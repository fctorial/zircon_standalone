#include <zircon/types.h>
#include "../out/bringup.qemu-x64/kernel_x64/gen/zircon/kernel/lib/userabi/vdso-code.h"
#include "elf.h"
#include "lib.h"

void init(zx_handle_t chan, void *vdso, int (*print)(const char *, ...)) {
  zx_status_t (*log)(char*, size_t) = vdso + VDSO_SYSCALL_zx_debug_write;
  zx_status_t (*exit)(int) = vdso + VDSO_SYSCALL_zx_process_exit;
  char buf[1024];
  log(buf, snprintf(buf, sizeof(buf), "%p\n", vdso));

  exit(35);
}

