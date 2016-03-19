# Copyright (c) 2016 Nuxi, https://nuxi.nl/
#
# This file is distributed under a 2-clause BSD license.
# See the LICENSE file for details.

from ..abi import *
from ..generator import *


class CGenerator(Generator):

    def __init__(self, prefix, header_guard=None, machine_dep=None,
                 md_prefix=None, md_type=None):
        super().__init__(comment_start='//')
        self.prefix = prefix
        self.header_guard = header_guard
        self.machine_dep = machine_dep
        self.md_prefix = md_prefix
        self.md_type = md_type

    def generate_head(self):
        super().generate_head()
        if self.header_guard is not None:
            print('#ifndef {}'.format(self.header_guard))
            print('#define {}'.format(self.header_guard))
            print()

    def generate_foot(self):
        if self.header_guard is not None:
            print('#endif')
        super().generate_foot()

    def ctypename(self, type):
        if isinstance(type, VoidType):
            return 'void'
        elif isinstance(type, IntType):
            if type.name == 'char':
                return 'char'
            return '{}_t'.format(type.name)
        elif (isinstance(type, IntLikeType) or
              isinstance(type, FunctionPointerType) or
              isinstance(type, StructType)):
            prefix = self.prefix
            if self.md_prefix is not None and type.layout.machine_dep:
                prefix = self.md_prefix
            return '{}{}_t'.format(prefix, type.name)

        else:
            raise Exception(
                'Unable to generate C type name for type: {}'.format(type))

    def cdecl(self, type, name=''):
        if (isinstance(type, VoidType) or
                isinstance(type, IntType) or
                isinstance(type, IntLikeType) or
                isinstance(type, StructType) or
                isinstance(type, FunctionPointerType)):
            return '{} {}'.format(self.ctypename(type), name).rstrip()

        elif isinstance(type, PointerType):
            decl = self.cdecl(type.target_type, '*{}'.format(name))
            if type.const:
                decl = 'const ' + decl
            return decl

        elif isinstance(type, ArrayType):
            if name.startswith('*'):
                name = '({})'.format(name)
            return self.cdecl(
                type.element_type, '{}[{}]'.format(
                    name, type.count))

        elif isinstance(type, AtomicType):
            return '_Atomic({}) {}'.format(
                self.cdecl(type.target_type), name).rstrip()

        else:
            raise Exception(
                'Unable to generate C type declaration for type: {}'.format(type))

    def ccast(self, type_from, type_to, name):
        if (isinstance(type_from, StructType) or
                isinstance(type_to, StructType)):
            return '*({})&{}'.format(
                self.cdecl(PointerType(False, type_to)), name)
        else:
            return '({}){}'.format(self.cdecl(type_to), name)

    def mi_type(self, mtype):
        if self.md_type is not None:
            if isinstance(mtype, PointerType) or mtype.name == 'size':
                return self.md_type
        return mtype


class CSyscalldefsGenerator(CGenerator):

    def generate_struct_members(self, type, indent=''):
        for m in type.raw_members:
            if isinstance(m, SimpleStructMember):
                mtype = self.mi_type(m.type)
                if mtype.layout.align[0] == mtype.layout.align[1]:
                    alignas = '_Alignas({}) '.format(mtype.layout.align[0])
                else:
                    alignas = ''
                print('{}{}{};'.format(
                    indent, alignas, self.cdecl(mtype, m.name)))
            elif isinstance(m, VariantStructMember):
                print('{}union {{'.format(indent))
                for x in m.members:
                    if x.name is None:
                        self.generate_struct_members(x.type, indent + '\t')
                    else:
                        print('{}\tstruct {{'.format(indent))
                        self.generate_struct_members(x.type, indent + '\t\t')
                        print('{}\t}} {};'.format(indent, x.name))
                print('{}}};'.format(indent))
            else:
                raise Exception('Unknown struct member: {}'.format(m))

    def generate_type(self, type):

        if self.machine_dep is not None:
            if type.layout.machine_dep != self.machine_dep:
                return

        if isinstance(type, IntLikeType):
            print('typedef {};'.format(self.cdecl(type.int_type,
                                                  self.ctypename(type))))
            if len(type.values) > 0:
                width = max(len(name) for val, name in type.values)
                if (isinstance(type, FlagsType) or
                        isinstance(type, OpaqueType)):
                    if len(type.values) == 1 and type.values[0][0] == 0:
                        val_format = 'd'
                    else:
                        val_format = '#0{}x'.format(
                            type.layout.size[0] * 2 + 2)
                else:
                    val_width = max(len(str(val)) for val, name in type.values)
                    val_format = '{}d'.format(val_width)

                for val, name in type.values:
                    print('#define {prefix}{cprefix}{name:{width}} '
                          '{val:{val_format}}'.format(
                              prefix=self.prefix.upper(),
                              cprefix=type.cprefix,
                              name=name.upper(),
                              width=width,
                              val=val,
                              val_format=val_format))

        elif isinstance(type, FunctionPointerType):
            parameters = []
            for p in type.parameters.raw_members:
                parameters.append(self.cdecl(self.mi_type(p.type), p.name))
            print('typedef {} (*{})({});'.format(
                self.cdecl(self.mi_type(type.return_type)),
                self.cdecl(type), ', '.join(parameters)))
            pass

        elif isinstance(type, StructType):
            typename = self.ctypename(type)

            print('typedef struct {')
            self.generate_struct_members(type, '\t')
            print('}} {};'.format(typename))

            self.generate_offset_asserts(typename, type.raw_members)
            self.generate_size_assert(typename, type.layout.size)
            self.generate_align_assert(typename, type.layout.align)

        else:
            raise Exception('Unknown class of type: {}'.format(type))

        print()

    def generate_offset_asserts(
            self, type_name, members, prefix='', offset=(0, 0)):
        for m in members:
            if isinstance(m, VariantMember):
                mprefix = prefix
                if m.name is not None:
                    mprefix += m.name + '.'
                self.generate_offset_asserts(
                    type_name, m.type.members, mprefix, offset)
            elif m.offset is not None:
                moffset = (offset[0] + m.offset[0], offset[1] + m.offset[1])
                if isinstance(m, VariantStructMember):
                    self.generate_offset_asserts(
                        type_name, m.members, prefix, moffset)
                else:
                    self.generate_offset_assert(
                        type_name, prefix + m.name, moffset)

    def generate_offset_assert(self, type_name, member_name, offset):
        self.generate_layout_assert(
            'offsetof({}, {})'.format(type_name, member_name), offset)

    def generate_size_assert(self, type_name, size):
        self.generate_layout_assert('sizeof({})'.format(type_name), size)

    def generate_align_assert(self, type_name, align):
        self.generate_layout_assert('_Alignof({})'.format(type_name), align)

    def generate_layout_assert(self, expression, value):
        static_assert = '_Static_assert({}, "Incorrect layout");'
        if value[0] == value[1] or (
                self.md_type is not None and
                self.md_type.layout.size in ((4, 4), (8, 8))):
            v = value[1]
            if self.md_type is not None and self.md_type.layout.size == (4, 4):
                v = value[0]
            print(static_assert.format('{} == {}'.format(expression, v)))
        else:
            voidptr = self.cdecl(PointerType(False, VoidType()))
            print(static_assert.format('sizeof({}) != 4 || {} == {}'.format(
                voidptr, expression, value[0])))
            print(static_assert.format('sizeof({}) != 8 || {} == {}'.format(
                voidptr, expression, value[1])))

    def generate_syscalls(self, syscalls):
        pass


class CSyscallsGenerator(CGenerator):

    def syscall_params(self, syscall):
        params = []
        for p in syscall.input.raw_members:
            params.append(self.cdecl(p.type, p.name))
        for p in syscall.output.raw_members:
            params.append(self.cdecl(PointerType(False, p.type), p.name))
        return params

    def generate_syscall(self, syscall):
        if syscall.noreturn:
            return_type = '_Noreturn void'
        else:
            return_type = '{}errno_t'.format(self.prefix)
        print('static inline {}'.format(return_type))
        print('{}sys_{}('.format(self.prefix, syscall.name), end='')
        params = self.syscall_params(syscall)
        if params == []:
            print('void', end='')
        else:
            print()
            for p in params[:-1]:
                print('\t{},'.format(p))
            print('\t{}'.format(params[-1]))
        print(')', end='')
        self.generate_syscall_body(syscall)
        print()

    def generate_syscall_body(self, syscall):
        print(';')

    def generate_types(self, types):
        pass


class CSyscallsImplGenerator(CSyscallsGenerator):

    def generate_syscall_body(self, syscall):
        print(' {')

        check_okay = len(syscall.output.raw_members) > 0

        n_regs = max(len(syscall.input.raw_members) + 1,
                     len(syscall.output.raw_members) +
                     self.output_register_start)
        for i in range(0, n_regs):
            print('\tregister {} asm("{}")'.format(
                  self.cdecl(self.register_t, "reg{}".format(i)),
                  self.registers[i]), end='')
            if i == 0:
                print(' = {};'.format(syscall.number))
            elif i - 1 < len(syscall.input.raw_members):
                p = syscall.input.raw_members[i - 1]
                print(' = {};'.format(
                      self.ccast(p.type, self.register_t, p.name)))
            else:
                print(';')
        if check_okay:
            print('\tregister char okay;')

        print('\tasm volatile (')
        print(self.asm)
        if check_okay:
            print(self.asm_check)

        first = True
        if check_okay:
            print('\t\t: "=r"(okay)')
            first = False
        for i in range(len(syscall.output.raw_members)):
            print('\t\t{} "=r"(reg{})'.format(':' if first else ',',
                                              i + self.output_register_start))
            first = False
        if first:
            print('\t\t:')

        for i in range(len(syscall.input.raw_members) + 1):
            print('\t\t{} "r"(reg{})'.format(':' if i == 0 else ',', i))

        print('\t\t: {});'.format(self.clobbers))
        if check_okay:
            print('\tif (okay) {')
            for i, p in enumerate(syscall.output.raw_members):
                print('\t\t*{} = {};'.format(
                    p.name,
                    self.ccast(self.register_t, p.type, "reg{}".format(
                        i + self.output_register_start))))
            print('\t\treturn 0;')
            print('\t}')

        if syscall.noreturn:
            print('\tfor (;;);')
        else:
            print('\treturn reg{};'.format(self.output_register_start))

        print('}')


class CSyscallsX86_64Generator(CSyscallsImplGenerator):

    registers = ['rax', 'rdi', 'rsi', 'rdx', 'r10', 'r8', 'r9']

    output_register_start = 0

    clobbers = '"memory", "rcx", "rdx", "r8", "r9", "r10", "r11"'

    register_t = int_types['uint64']

    asm = '\t\t"\\tsyscall\\n"'
    asm_check = '\t\t"\\tsetnc %0\\n"'

class CSyscallsAarch64Generator(CSyscallsImplGenerator):

    registers = ['x8', 'x0', 'x1', 'x2', 'x3', 'x4', 'x5']

    output_register_start = 1

    clobbers = ('"memory"\n'
        '\t\t, "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7"\n'
        '\t\t, "x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15"\n'
        '\t\t, "x16", "x17", "x18"\n'
        '\t\t, "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7"')

    register_t = int_types['uint64']

    asm = '\t\t"\\tsvc 0\\n"'
    asm_check = '\t\t"\\tcset %0, cc\\n"'
