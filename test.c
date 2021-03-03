#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void init(zx_handle_t chan, void *vdso, int (*printf)(const char*, ...));

int main() {
//  char* path = "/home/fctorial/src/fuchsia/fuchsia/out/bringup.qemu-x64/user.vdso_x64/libzircon.so.debug";
  char* path = "/home/fctorial/src/fuchsia/fuchsia/out/bringup.qemu-x64/libzircon.so";
  int fd = open(path, O_RDONLY);
  int size = lseek(fd, (size_t) 0, SEEK_END);
  lseek(fd, (size_t) 0, SEEK_SET);
  void* vdso = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
  init(0, vdso, printf);
  return 5;
}
