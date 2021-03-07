#include <libs/linker/linker.h>
#include <zircon/boot/bootfs.h>

int dprintf(const char *fmt, ...);

int dlog(const char *key, char *fmt, ...);

void print_strings(char *start, int num);

const char* zx_status_get_string(zx_status_t status);

size_t get_vmo_size(zx_handle_t vmo);

zbi_bootfs_dirent_t* bootfs_find_file(zbi_bootfs_header_t* bootfs, char* name);

typedef struct {
  size_t exec_start;
  size_t exec_end;
} vdso_load_info;

bool get_vdso_load_info(zx_handle_t vmo, vdso_load_info* info);
