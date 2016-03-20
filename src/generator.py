# Copyright (c) 2016 Nuxi, https://nuxi.nl/
#
# This file is distributed under a 2-clause BSD license.
# See the LICENSE file for details.

from .abi import *


class Generator:

    def __init__(self,
                 comment_prefix='',
                 comment_begin=None,
                 comment_end=None):
        self.comment_begin= comment_begin
        self.comment_prefix = comment_prefix
        self.comment_end = comment_end

    def generate_head(self):
        self.generate_license()
        print()
        if self.comment_begin is not None:
            print(self.comment_begin)
        print(self.comment_prefix + 'This file is automatically generated.')
        if self.comment_end is not None:
            print(self.comment_end)
        print()

    def generate_foot(self):
        pass

    def generate_type(self, type):
        pass

    def generate_syscall(self, syscall):
        pass

    def generate_types(self, types):
        first_pass = True
        generate_now = [name for name in sorted(types)]
        generate_later = []
        generated = set()

        while generate_now != []:
            for type_name in generate_now:
                type = types[type_name]

                if (not (getattr(type, 'dependencies', set()) <= generated) or
                        (first_pass and not isinstance(type, IntLikeType))):
                    generate_later.append(type_name)
                else:
                    self.generate_type(type)
                    generated.add(type_name)

            generate_now = generate_later
            generate_later = []
            first_pass = False

        assert(generated == {n for n in types})

    def generate_syscalls(self, syscalls):
        for syscall in sorted(syscalls):
            self.generate_syscall(syscalls[syscall])

    def generate_license(self):
        import os
        license = os.path.dirname(__file__) + '/../LICENSE'
        if self.comment_begin is not None:
            print(self.comment_begin)
        with open(license) as f:
            skipping = True
            for line in f:
                if skipping:
                    if line.strip() == '':
                        skipping = False
                else:
                    print((self.comment_prefix + line[2:]).rstrip())
        if self.comment_end is not None:
            print(self.comment_end)

    def generate_abi(self, abi):
        self.generate_head()
        self.generate_types(abi.types)
        self.generate_syscalls(abi.syscalls_by_name)
        self.generate_foot()
