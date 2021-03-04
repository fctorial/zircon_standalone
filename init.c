#include <zircon/types.h>
#include <zircon/processargs.h>
#include "lib.h"
#include "out/linker.h"

int dprintf(const char *fmt, ...) {
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  int result = vsnprintf(buf, 1024, fmt, args);
  zx_debug_write(buf, result);
  va_end(args);
  return result;
}

void init(zx_handle_t chan, void *vdso) {
  link_dependent(vdso);
  dprintf("=============================\n");

  dprintf("=============================\n");
  zx_process_exit(23);
}
