#include <zircon/types.h>
#include <zircon/processargs.h>
#include "../out/bringup.qemu-x64/kernel_x64/gen/zircon/kernel/lib/userabi/vdso-code.h"
#include "elf.h"
#include "lib.h"

zx_status_t (*dlog)(char *, size_t);

zx_status_t (*process_exit)(int);

zx_status_t (*channel_read)(zx_handle_t handle,
                            uint32_t options,
                            void *bytes,
                            zx_handle_t *handles,
                            uint32_t num_bytes,
                            uint32_t num_handles,
                            uint32_t *actual_bytes,
                            uint32_t *actual_handles);

zx_status_t (*channel_write)(zx_handle_t handle,
                             uint32_t options,
                             const void *bytes,
                             uint32_t num_bytes,
                             const zx_handle_t *handles,
                             uint32_t num_handles);

zx_status_t (*channel_create)(uint32_t options,
                              zx_handle_t *out0,
                              zx_handle_t *out1);

zx_status_t (*process_create)(zx_handle_t job,
                              const char *name,
                              size_t name_size,
                              uint32_t options,
                              zx_handle_t *proc_handle,
                              zx_handle_t *vmar_handle);

zx_status_t (*process_start)(zx_handle_t handle,
                             zx_handle_t thread,
                             zx_vaddr_t entry,
                             zx_vaddr_t stack,
                             zx_handle_t arg1,
                             uintptr_t arg2);


int dprintf(const char *fmt, ...) {
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  int result = vsnprintf(buf, 1024, fmt, args);
  dlog(buf, result);
  va_end(args);
  return result;
}

volatile long i = 0;

void init(zx_handle_t chan, void *vdso) {
  process_exit = vdso + VDSO_SYSCALL_zx_process_exit;
  dlog = vdso + VDSO_SYSCALL_zx_debug_write;
  channel_create = vdso + VDSO_SYSCALL_zx_channel_create;
  channel_read = vdso + VDSO_SYSCALL_zx_channel_read;
  channel_write = vdso + VDSO_SYSCALL_zx_channel_write;
  process_create = vdso + VDSO_SYSCALL_zx_process_create;
  process_start = vdso + VDSO_SYSCALL_zx_process_start;

  dprintf("=============================\n");
  for (i=0; i<1000000000; i++) {}

  char bs[8192];
  zx_handle_t hs[32];
  uint32_t bsc;
  uint32_t hsc;


  zx_status_t status = channel_read(chan, 0, bs, hs, 8192, 32, &bsc, &hsc);

  dprintf("%p\n", status);

  dprintf("%s\t%d\t%d\n", bs, bsc, hsc);

//  zx_handle_t c, _c;
//  channel_create(0, &c, &_c);
//  dprintf("%p\n%p\n", c, _c);

  dprintf("=============================\n");
  process_exit(35);
}

