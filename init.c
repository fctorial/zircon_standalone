#include "build/processargs.h"
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

int dlog(char* key, char* fmt, ...) {
  int res1 = dprintf("%-30s", key);
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  int res2 = vsnprintf(buf, 1024, fmt, args);
  zx_debug_write(buf, res2);
  zx_debug_write("\n", 1);
  va_end(args);
  return res1 + res2 + 1;
}

void print_strings(char* start, int num) {
  while (num--) {
    int read = dprintf("%s\n", start);
    start += read;
  }
}

void print_environment(struct zx_proc_args* args) {
  char* base = (char *) args;
  dprintf("args:----------------------\n");
  print_strings(base + args->args_off, args->args_num);
  dprintf("environment:----------------\n");
  print_strings(base + args->environ_off, args->environ_num);
  dprintf("names:----------------------\n");
  print_strings(base + args->names_off, args->names_num);
}

extern const void* __ehdr_start;

void init(zx_handle_t chan, void *vdso) {
  link_dependent(vdso);

  dprintf("=============================\n");

  uint32_t bsc, hsc;
  processargs_message_size(chan, &bsc, &hsc);

  char bs[bsc];
  zx_handle_t hs[hsc];
  struct zx_proc_args* args;
  uint32_t* handle_infos;
  processargs_read(chan, bs, bsc, hs, hsc, &args, &handle_infos);

  handles_container_t handles;
  processargs_extract_handles(hsc, hs, handle_infos, &handles);

  dprintf("=============================\n");
  zx_process_exit(23);
}
