#include <build/syscalls.h>

#define SYSCALL(name, ...) extern typeof(_##name)* name;
#include "syscalls.inc"
#undef SYSCALL

void link(void* vdso);
