#ifndef SYSROOT_ZIRCON_SYSCALLS_H_
#define SYSROOT_ZIRCON_SYSCALLS_H_

#define _ZX_SYSCALL_DECL(name, type, attrs, nargs, arglist, prototype) \
  extern attrs type __zx_##name prototype;
#define _ZX_SYSCALL_ANNO(attr)

#include <zircon/syscalls/internal/cdecls.inc>

#undef _ZX_SYSCALL_ANNO
#undef _ZX_SYSCALL_DECL

#endif
