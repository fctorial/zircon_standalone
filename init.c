#include <zircon/types.h>
#include <zircon/processargs.h>
#include <zircon/syscalls.h>
#include "../out/bringup.qemu-x64/kernel_x64/gen/zircon/kernel/lib/userabi/vdso-code.h"
#include "elf.h"
#include "lib.h"
#include "build/linker.h"

int dprintf(const char *fmt, ...) {
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  int result = vsnprintf(buf, 1024, fmt, args);
  sys_debug_write(buf, result);
  va_end(args);
  return result;
}

void init(zx_handle_t chan, void *vdso) {
  link_dependent(vdso);
  dprintf("=============================\n");

//  char bs[8192];
//  zx_handle_t hs[32];
//  uint32_t bsc;
//  uint32_t hsc;
//
//
//  zx_status_t status = channel_read(chan, 0, bs, hs, 8192, 32, &bsc, &hsc);
//
//  dprintf("%p\n", status);
//
//  dprintf("%s\t%d\t%d\n", bs, bsc, hsc);

//  zx_handle_t c, _c;
//  channel_create(0, &c, &_c);
//  dprintf("%p\n%p\n", c, _c);

  dprintf("=============================\n");
  sys_process_exit(35);
}

