// Copyright (c) 2016 Nuxi (https://nuxi.nl/) and contributors.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
//
// This file is automatically generated. Do not edit.
//
// Source: https://github.com/NuxiNL/cloudabi

#include <asm/byteorder.h>

#include "cloudabi_syscalls.h"
#include "cloudabi64_syscalls.h"

#ifdef __LITTLE_ENDIAN
#define MEMBER(type, name) _Alignas(8) type name
#else
#define PAD(type) \
    ((sizeof(uint64_t) - (sizeof(type) % sizeof(uint64_t))) % sizeof(uint64_t))
#define MEMBER(type, name) char name##_pad[PAD(type)]; type name
#endif

static cloudabi_errno_t do_clock_res_get(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_clockid_t, clock_id);
	} *vin = in;
	struct {
		MEMBER(cloudabi_timestamp_t, resolution);
	} *vout = out;
	return cloudabi_sys_clock_res_get(vin->clock_id, &vout->resolution);
}

static cloudabi_errno_t do_clock_time_get(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_clockid_t, clock_id);
		MEMBER(cloudabi_timestamp_t, precision);
	} *vin = in;
	struct {
		MEMBER(cloudabi_timestamp_t, time);
	} *vout = out;
	return cloudabi_sys_clock_time_get(vin->clock_id, vin->precision, &vout->time);
}

static cloudabi_errno_t do_condvar_signal(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_condvar_t __user *, condvar);
		MEMBER(cloudabi_scope_t, scope);
		MEMBER(cloudabi_nthreads_t, nwaiters);
	} *vin = in;
	return cloudabi_sys_condvar_signal(vin->condvar, vin->scope, vin->nwaiters);
}

static cloudabi_errno_t do_fd_close(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
	} *vin = in;
	return cloudabi_sys_fd_close(vin->fd);
}

static cloudabi_errno_t do_fd_create1(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_filetype_t, type);
	} *vin = in;
	struct {
		MEMBER(cloudabi_fd_t, fd);
	} *vout = out;
	return cloudabi_sys_fd_create1(vin->type, &vout->fd);
}

static cloudabi_errno_t do_fd_create2(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_filetype_t, type);
	} *vin = in;
	struct {
		MEMBER(cloudabi_fd_t, fd1);
		MEMBER(cloudabi_fd_t, fd2);
	} *vout = out;
	return cloudabi_sys_fd_create2(vin->type, &vout->fd1, &vout->fd2);
}

static cloudabi_errno_t do_fd_datasync(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
	} *vin = in;
	return cloudabi_sys_fd_datasync(vin->fd);
}

static cloudabi_errno_t do_fd_dup(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, from);
	} *vin = in;
	struct {
		MEMBER(cloudabi_fd_t, fd);
	} *vout = out;
	return cloudabi_sys_fd_dup(vin->from, &vout->fd);
}

static cloudabi_errno_t do_fd_pread(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const cloudabi64_iovec_t __user *, iov);
		MEMBER(size_t, iovcnt);
		MEMBER(cloudabi_filesize_t, offset);
	} *vin = in;
	struct {
		MEMBER(size_t, nread);
	} *vout = out;
	return cloudabi64_sys_fd_pread(vin->fd, vin->iov, vin->iovcnt, vin->offset, &vout->nread);
}

static cloudabi_errno_t do_fd_pwrite(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const cloudabi64_ciovec_t __user *, iov);
		MEMBER(size_t, iovcnt);
		MEMBER(cloudabi_filesize_t, offset);
	} *vin = in;
	struct {
		MEMBER(size_t, nwritten);
	} *vout = out;
	return cloudabi64_sys_fd_pwrite(vin->fd, vin->iov, vin->iovcnt, vin->offset, &vout->nwritten);
}

static cloudabi_errno_t do_fd_read(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const cloudabi64_iovec_t __user *, iov);
		MEMBER(size_t, iovcnt);
	} *vin = in;
	struct {
		MEMBER(size_t, nread);
	} *vout = out;
	return cloudabi64_sys_fd_read(vin->fd, vin->iov, vin->iovcnt, &vout->nread);
}

static cloudabi_errno_t do_fd_replace(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, from);
		MEMBER(cloudabi_fd_t, to);
	} *vin = in;
	return cloudabi_sys_fd_replace(vin->from, vin->to);
}

static cloudabi_errno_t do_fd_seek(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(cloudabi_filedelta_t, offset);
		MEMBER(cloudabi_whence_t, whence);
	} *vin = in;
	struct {
		MEMBER(cloudabi_filesize_t, newoffset);
	} *vout = out;
	return cloudabi_sys_fd_seek(vin->fd, vin->offset, vin->whence, &vout->newoffset);
}

static cloudabi_errno_t do_fd_stat_get(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(cloudabi_fdstat_t __user *, buf);
	} *vin = in;
	return cloudabi_sys_fd_stat_get(vin->fd, vin->buf);
}

static cloudabi_errno_t do_fd_stat_put(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const cloudabi_fdstat_t __user *, buf);
		MEMBER(cloudabi_fdsflags_t, flags);
	} *vin = in;
	return cloudabi_sys_fd_stat_put(vin->fd, vin->buf, vin->flags);
}

static cloudabi_errno_t do_fd_sync(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
	} *vin = in;
	return cloudabi_sys_fd_sync(vin->fd);
}

static cloudabi_errno_t do_fd_write(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const cloudabi64_ciovec_t __user *, iov);
		MEMBER(size_t, iovcnt);
	} *vin = in;
	struct {
		MEMBER(size_t, nwritten);
	} *vout = out;
	return cloudabi64_sys_fd_write(vin->fd, vin->iov, vin->iovcnt, &vout->nwritten);
}

static cloudabi_errno_t do_file_advise(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(cloudabi_filesize_t, offset);
		MEMBER(cloudabi_filesize_t, len);
		MEMBER(cloudabi_advice_t, advice);
	} *vin = in;
	return cloudabi_sys_file_advise(vin->fd, vin->offset, vin->len, vin->advice);
}

static cloudabi_errno_t do_file_allocate(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(cloudabi_filesize_t, offset);
		MEMBER(cloudabi_filesize_t, len);
	} *vin = in;
	return cloudabi_sys_file_allocate(vin->fd, vin->offset, vin->len);
}

static cloudabi_errno_t do_file_create(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const char __user *, path);
		MEMBER(size_t, pathlen);
		MEMBER(cloudabi_filetype_t, type);
	} *vin = in;
	return cloudabi_sys_file_create(vin->fd, vin->path, vin->pathlen, vin->type);
}

static cloudabi_errno_t do_file_link(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_lookup_t, fd1);
		MEMBER(const char __user *, path1);
		MEMBER(size_t, path1len);
		MEMBER(cloudabi_fd_t, fd2);
		MEMBER(const char __user *, path2);
		MEMBER(size_t, path2len);
	} *vin = in;
	return cloudabi_sys_file_link(vin->fd1, vin->path1, vin->path1len, vin->fd2, vin->path2, vin->path2len);
}

static cloudabi_errno_t do_file_open(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_lookup_t, dirfd);
		MEMBER(const char __user *, path);
		MEMBER(size_t, pathlen);
		MEMBER(cloudabi_oflags_t, oflags);
		MEMBER(const cloudabi_fdstat_t __user *, fds);
	} *vin = in;
	struct {
		MEMBER(cloudabi_fd_t, fd);
	} *vout = out;
	return cloudabi_sys_file_open(vin->dirfd, vin->path, vin->pathlen, vin->oflags, vin->fds, &vout->fd);
}

static cloudabi_errno_t do_file_readdir(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(void __user *, buf);
		MEMBER(size_t, nbyte);
		MEMBER(cloudabi_dircookie_t, cookie);
	} *vin = in;
	struct {
		MEMBER(size_t, bufused);
	} *vout = out;
	return cloudabi_sys_file_readdir(vin->fd, vin->buf, vin->nbyte, vin->cookie, &vout->bufused);
}

static cloudabi_errno_t do_file_readlink(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const char __user *, path);
		MEMBER(size_t, pathlen);
		MEMBER(char __user *, buf);
		MEMBER(size_t, bufsize);
	} *vin = in;
	struct {
		MEMBER(size_t, bufused);
	} *vout = out;
	return cloudabi_sys_file_readlink(vin->fd, vin->path, vin->pathlen, vin->buf, vin->bufsize, &vout->bufused);
}

static cloudabi_errno_t do_file_rename(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, oldfd);
		MEMBER(const char __user *, old);
		MEMBER(size_t, oldlen);
		MEMBER(cloudabi_fd_t, newfd);
		MEMBER(const char __user *, new);
		MEMBER(size_t, newlen);
	} *vin = in;
	return cloudabi_sys_file_rename(vin->oldfd, vin->old, vin->oldlen, vin->newfd, vin->new, vin->newlen);
}

static cloudabi_errno_t do_file_stat_fget(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(cloudabi_filestat_t __user *, buf);
	} *vin = in;
	return cloudabi_sys_file_stat_fget(vin->fd, vin->buf);
}

static cloudabi_errno_t do_file_stat_fput(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const cloudabi_filestat_t __user *, buf);
		MEMBER(cloudabi_fsflags_t, flags);
	} *vin = in;
	return cloudabi_sys_file_stat_fput(vin->fd, vin->buf, vin->flags);
}

static cloudabi_errno_t do_file_stat_get(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_lookup_t, fd);
		MEMBER(const char __user *, path);
		MEMBER(size_t, pathlen);
		MEMBER(cloudabi_filestat_t __user *, buf);
	} *vin = in;
	return cloudabi_sys_file_stat_get(vin->fd, vin->path, vin->pathlen, vin->buf);
}

static cloudabi_errno_t do_file_stat_put(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_lookup_t, fd);
		MEMBER(const char __user *, path);
		MEMBER(size_t, pathlen);
		MEMBER(const cloudabi_filestat_t __user *, buf);
		MEMBER(cloudabi_fsflags_t, flags);
	} *vin = in;
	return cloudabi_sys_file_stat_put(vin->fd, vin->path, vin->pathlen, vin->buf, vin->flags);
}

static cloudabi_errno_t do_file_symlink(const void *in, void *out)
{
	const struct {
		MEMBER(const char __user *, path1);
		MEMBER(size_t, path1len);
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const char __user *, path2);
		MEMBER(size_t, path2len);
	} *vin = in;
	return cloudabi_sys_file_symlink(vin->path1, vin->path1len, vin->fd, vin->path2, vin->path2len);
}

static cloudabi_errno_t do_file_unlink(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const char __user *, path);
		MEMBER(size_t, pathlen);
		MEMBER(cloudabi_ulflags_t, flags);
	} *vin = in;
	return cloudabi_sys_file_unlink(vin->fd, vin->path, vin->pathlen, vin->flags);
}

static cloudabi_errno_t do_lock_unlock(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_lock_t __user *, lock);
		MEMBER(cloudabi_scope_t, scope);
	} *vin = in;
	return cloudabi_sys_lock_unlock(vin->lock, vin->scope);
}

static cloudabi_errno_t do_mem_advise(const void *in, void *out)
{
	const struct {
		MEMBER(void __user *, addr);
		MEMBER(size_t, len);
		MEMBER(cloudabi_advice_t, advice);
	} *vin = in;
	return cloudabi_sys_mem_advise(vin->addr, vin->len, vin->advice);
}

static cloudabi_errno_t do_mem_lock(const void *in, void *out)
{
	const struct {
		MEMBER(const void __user *, addr);
		MEMBER(size_t, len);
	} *vin = in;
	return cloudabi_sys_mem_lock(vin->addr, vin->len);
}

static cloudabi_errno_t do_mem_map(const void *in, void *out)
{
	const struct {
		MEMBER(void __user *, addr);
		MEMBER(size_t, len);
		MEMBER(cloudabi_mprot_t, prot);
		MEMBER(cloudabi_mflags_t, flags);
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(cloudabi_filesize_t, off);
	} *vin = in;
	struct {
		MEMBER(void __user *, mem);
	} *vout = out;
	return cloudabi_sys_mem_map(vin->addr, vin->len, vin->prot, vin->flags, vin->fd, vin->off, &vout->mem);
}

static cloudabi_errno_t do_mem_protect(const void *in, void *out)
{
	const struct {
		MEMBER(void __user *, addr);
		MEMBER(size_t, len);
		MEMBER(cloudabi_mprot_t, prot);
	} *vin = in;
	return cloudabi_sys_mem_protect(vin->addr, vin->len, vin->prot);
}

static cloudabi_errno_t do_mem_sync(const void *in, void *out)
{
	const struct {
		MEMBER(void __user *, addr);
		MEMBER(size_t, len);
		MEMBER(cloudabi_msflags_t, flags);
	} *vin = in;
	return cloudabi_sys_mem_sync(vin->addr, vin->len, vin->flags);
}

static cloudabi_errno_t do_mem_unlock(const void *in, void *out)
{
	const struct {
		MEMBER(const void __user *, addr);
		MEMBER(size_t, len);
	} *vin = in;
	return cloudabi_sys_mem_unlock(vin->addr, vin->len);
}

static cloudabi_errno_t do_mem_unmap(const void *in, void *out)
{
	const struct {
		MEMBER(void __user *, addr);
		MEMBER(size_t, len);
	} *vin = in;
	return cloudabi_sys_mem_unmap(vin->addr, vin->len);
}

static cloudabi_errno_t do_poll(const void *in, void *out)
{
	const struct {
		MEMBER(const cloudabi64_subscription_t __user *, in);
		MEMBER(cloudabi64_event_t __user *, out);
		MEMBER(size_t, nsubscriptions);
	} *vin = in;
	struct {
		MEMBER(size_t, nevents);
	} *vout = out;
	return cloudabi64_sys_poll(vin->in, vin->out, vin->nsubscriptions, &vout->nevents);
}

static cloudabi_errno_t do_poll_fd(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const cloudabi64_subscription_t __user *, in);
		MEMBER(size_t, nin);
		MEMBER(cloudabi64_event_t __user *, out);
		MEMBER(size_t, nout);
		MEMBER(const cloudabi64_subscription_t __user *, timeout);
	} *vin = in;
	struct {
		MEMBER(size_t, nevents);
	} *vout = out;
	return cloudabi64_sys_poll_fd(vin->fd, vin->in, vin->nin, vin->out, vin->nout, vin->timeout, &vout->nevents);
}

static cloudabi_errno_t do_proc_exec(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const void __user *, data);
		MEMBER(size_t, datalen);
		MEMBER(const cloudabi_fd_t __user *, fds);
		MEMBER(size_t, fdslen);
	} *vin = in;
	return cloudabi_sys_proc_exec(vin->fd, vin->data, vin->datalen, vin->fds, vin->fdslen);
}

static cloudabi_errno_t do_proc_exit(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_exitcode_t, rval);
	} *vin = in;
	cloudabi_sys_proc_exit(vin->rval);
	return 0;
}

static cloudabi_errno_t do_proc_fork(const void *in, void *out)
{
	struct {
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(cloudabi_tid_t, tid);
	} *vout = out;
	return cloudabi_sys_proc_fork(&vout->fd, &vout->tid);
}

static cloudabi_errno_t do_proc_raise(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_signal_t, sig);
	} *vin = in;
	return cloudabi_sys_proc_raise(vin->sig);
}

static cloudabi_errno_t do_random_get(const void *in, void *out)
{
	const struct {
		MEMBER(void __user *, buf);
		MEMBER(size_t, nbyte);
	} *vin = in;
	return cloudabi_sys_random_get(vin->buf, vin->nbyte);
}

static cloudabi_errno_t do_sock_accept(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, sock);
		MEMBER(cloudabi_sockstat_t __user *, buf);
	} *vin = in;
	struct {
		MEMBER(cloudabi_fd_t, conn);
	} *vout = out;
	return cloudabi_sys_sock_accept(vin->sock, vin->buf, &vout->conn);
}

static cloudabi_errno_t do_sock_bind(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, sock);
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const char __user *, path);
		MEMBER(size_t, pathlen);
	} *vin = in;
	return cloudabi_sys_sock_bind(vin->sock, vin->fd, vin->path, vin->pathlen);
}

static cloudabi_errno_t do_sock_connect(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, sock);
		MEMBER(cloudabi_fd_t, fd);
		MEMBER(const char __user *, path);
		MEMBER(size_t, pathlen);
	} *vin = in;
	return cloudabi_sys_sock_connect(vin->sock, vin->fd, vin->path, vin->pathlen);
}

static cloudabi_errno_t do_sock_listen(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, sock);
		MEMBER(cloudabi_backlog_t, backlog);
	} *vin = in;
	return cloudabi_sys_sock_listen(vin->sock, vin->backlog);
}

static cloudabi_errno_t do_sock_recv(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, sock);
		MEMBER(const cloudabi64_recv_in_t __user *, in);
		MEMBER(cloudabi64_recv_out_t __user *, out);
	} *vin = in;
	return cloudabi64_sys_sock_recv(vin->sock, vin->in, vin->out);
}

static cloudabi_errno_t do_sock_send(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, sock);
		MEMBER(const cloudabi64_send_in_t __user *, in);
		MEMBER(cloudabi64_send_out_t __user *, out);
	} *vin = in;
	return cloudabi64_sys_sock_send(vin->sock, vin->in, vin->out);
}

static cloudabi_errno_t do_sock_shutdown(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, sock);
		MEMBER(cloudabi_sdflags_t, how);
	} *vin = in;
	return cloudabi_sys_sock_shutdown(vin->sock, vin->how);
}

static cloudabi_errno_t do_sock_stat_get(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_fd_t, sock);
		MEMBER(cloudabi_sockstat_t __user *, buf);
		MEMBER(cloudabi_ssflags_t, flags);
	} *vin = in;
	return cloudabi_sys_sock_stat_get(vin->sock, vin->buf, vin->flags);
}

static cloudabi_errno_t do_thread_create(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi64_threadattr_t __user *, attr);
	} *vin = in;
	struct {
		MEMBER(cloudabi_tid_t, tid);
	} *vout = out;
	return cloudabi64_sys_thread_create(vin->attr, &vout->tid);
}

static cloudabi_errno_t do_thread_exit(const void *in, void *out)
{
	const struct {
		MEMBER(cloudabi_lock_t __user *, lock);
		MEMBER(cloudabi_scope_t, scope);
	} *vin = in;
	cloudabi_sys_thread_exit(vin->lock, vin->scope);
	return 0;
}

static cloudabi_errno_t do_thread_tcb_set(const void *in, void *out)
{
	const struct {
		MEMBER(void __user *, tcb);
	} *vin = in;
	return cloudabi_sys_thread_tcb_set(vin->tcb);
}

static cloudabi_errno_t do_thread_yield(const void *in, void *out)
{
	return cloudabi_sys_thread_yield();
}

static cloudabi_errno_t do_enosys(void *in, void *out)
{
	return CLOUDABI_ENOSYS;
}

cloudabi_errno_t (*cloudabi64_syscalls[])(const void *, void *) = {
	do_clock_res_get,
	do_clock_time_get,
	do_condvar_signal,
	do_fd_close,
	do_fd_create1,
	do_fd_create2,
	do_fd_datasync,
	do_fd_dup,
	do_fd_pread,
	do_fd_pwrite,
	do_fd_read,
	do_fd_replace,
	do_fd_seek,
	do_fd_stat_get,
	do_fd_stat_put,
	do_fd_sync,
	do_fd_write,
	do_file_advise,
	do_file_allocate,
	do_file_create,
	do_file_link,
	do_file_open,
	do_file_readdir,
	do_file_readlink,
	do_file_rename,
	do_file_stat_fget,
	do_file_stat_fput,
	do_file_stat_get,
	do_file_stat_put,
	do_file_symlink,
	do_file_unlink,
	do_lock_unlock,
	do_mem_advise,
	do_mem_lock,
	do_mem_map,
	do_mem_protect,
	do_mem_sync,
	do_mem_unlock,
	do_mem_unmap,
	do_poll,
	do_proc_exec,
	do_proc_exit,
	do_proc_fork,
	do_proc_raise,
	do_random_get,
	do_sock_accept,
	do_sock_bind,
	do_sock_connect,
	do_sock_listen,
	do_sock_recv,
	do_sock_send,
	do_sock_shutdown,
	do_sock_stat_get,
	do_thread_create,
	do_thread_exit,
	do_thread_tcb_set,
	do_thread_yield,
	do_poll_fd,

	do_enosys,
};
