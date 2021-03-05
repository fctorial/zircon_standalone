#include <zircon/string_view.h>
#include <zircon/syscalls/object.h>
#include <zircon/syscalls/pci.h>
#include <zircon/syscalls/profile.h>
#include <zircon/syscalls/types.h>
#include <zircon/types.h>
#include <libs/headers/syscall_signatures.h>

#define SYSCALL(name, ...) extern typeof(__##name)* name;
#include "syscalls.inc"
#undef SYSCALL

void link(void* vdso);
