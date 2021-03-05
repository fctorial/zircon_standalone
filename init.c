#include <libs/procargs/processargs.h>
#include <libs/utils/stdlib.h>
#include <libs/utils/zk.h>
#include <libs/headers/elf.h>
#include <libs/linker/linker.h>

void child_init(zx_handle_t _, void* vdso) {
  link(vdso);
  zx_debug_write("mama\n", 5);
  zx_process_exit(0);
}

void init(zx_handle_t chan, void *vdso) {
  link(vdso);

  dprintf("=============================\n");
  handles_container_t handles;
  memset(&handles, 0, sizeof(handles));
  extract_handles_chan(chan, &handles);

  size_t vdso_size = -1;
  zx_status_t status;
  status = zx_vmo_get_size(handles.vmo_vdso, &vdso_size);
  if (status != ZX_OK) {
    dlog("vdso size fetch failed", "%s", zx_status_get_string(status));
    zx_process_exit(1);
  } else {
    dlog("vdso size", "%d", vdso_size);
  }

  zx_handle_t child, cvmar, cthread, cmem, cvdso;
  dlog("zx_process_create", "%s", zx_status_get_string(zx_process_create(handles.job_default, "child", 5, 0, &child, &cvmar)));
  dlog("zx_vmo_create", "%s", zx_status_get_string(zx_vmo_create(128 * 1024, 0, &cmem)));
//  dlog("zx_vmo_write", "%s", zx_status_get_string(zx_vmo_write(cmem, __ehdr_start, 0, __ehdr_start->e_shoff)));
//  dlog("zx_vmar_map", "%s", zx_status_get_string(zx_vmar_map(cvmar, 0, (size_t) __ehdr_start, cmem, 0, 128 * 1024, NULL)));
//  dlog("zx_vmo_create", "%s", zx_status_get_string(zx_vmo_create(vdso_size, 0, &cvdso)));
//  dlog("zx_vmo_write", "%s", zx_status_get_string(zx_vmo_write(cmem, vdso, 0, vdso_size)));
//  dlog("zx_vmar_map", "%s", zx_status_get_string(zx_vmar_map(cvmar, 0, (size_t) vdso, cvdso, 0, vdso_size, NULL)));
//  dlog("zx_thread_create", "%s", zx_status_get_string(zx_thread_create(child, "child_thread", 12, 0, &cthread)));
//  dlog("zx_process_start", "%s", zx_status_get_string(zx_process_start(child, cthread, (zx_vaddr_t) child_init, (zx_vaddr_t) ((void *) __ehdr_start + __ehdr_start->e_shoff + 2048), 0, 0)));
  dprintf("=============================\n");

//  zx_nanosleep(zx_duration_from_min(10));
  zx_process_exit(23);
}
