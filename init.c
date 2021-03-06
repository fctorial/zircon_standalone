#include <libs/procargs/processargs.h>
#include <libs/utils/stdlib.h>
#include <libs/utils/zk.h>
#include <libs/linker/linker.h>

void child_init(zx_handle_t _, size_t *vdso) {
  typeof(zx_debug_write) write = (typeof(zx_debug_write)) vdso[0];
  typeof(zx_process_exit) exit = (typeof(zx_process_exit)) vdso[1];
  write("mama\n", 5);
  exit(0);
}

void init(zx_handle_t chan, void *vdso) {
  link(vdso);

  dprintf("=============================\n");
  handles_container_t handles;
  memset(&handles, 0, sizeof(handles));
  extract_handles_chan(chan, &handles);

  zbi_bootfs_header_t *bootfs;
  zx_vmar_map(handles.vmar_root, ZX_VM_PERM_READ, 0, handles.vmo_bootfs, 0, get_vmo_size(handles.vmo_bootfs), (zx_vaddr_t *) &bootfs);
  zbi_bootfs_dirent_t *ent = bootfs_find_file(bootfs, "bin/init");
  dlog("bin/init size:", "%d", ent->data_len);

  dprintf("=============================\n");

  zx_process_exit(23);















  zx_handle_close(handles.ldsvc);
  size_t vdso_size = 0;
  zx_status_t status;
  status = zx_vmo_get_size(handles.vmo_vdso, &vdso_size);
  if (status != ZX_OK) {
    dlog("vdso size fetch failed", "%s", zx_status_get_string(status));
    zx_process_exit(1);
  } else {
    dlog("vdso size", "%d", vdso_size);
  }

  const size_t child_mem_size = 8 * 1024;
  zx_handle_t child, cvmar, cthread, cmem;
  dlog("zx_process_create", "%s",
       zx_status_get_string(zx_process_create(handles.job_default, "child", 5, 0, &child, &cvmar)));
  dlog("zx_thread_create", "%s", zx_status_get_string(zx_thread_create(child, "child_thread", 12, 0, &cthread)));
  size_t vdso_addr;
  dlog("zx_vmar_map vdso", "%s", zx_status_get_string(
    zx_vmar_map(cvmar, ZX_VM_PERM_READ | ZX_VM_PERM_EXECUTE, (size_t) 0, handles.vmo_vdso, 0x7000, vdso_size - 0x7000,
                &vdso_addr)));
  dlog("zx_vmo_create cmem", "%s", zx_status_get_string(zx_vmo_create(child_mem_size, 0, &cmem)));
  dlog("zx_vmo_replace_as_executable cmem", "%s",
       zx_status_get_string(zx_vmo_replace_as_executable(cmem, ZX_HANDLE_INVALID, &cmem)));
  int func_size = 512;
  dlog("zx_vmo_write executable", "%s", zx_status_get_string(zx_vmo_write(cmem, child_init, 0, func_size)));
  size_t child_entry;
  dlog("zx_vmar_map", "%s", zx_status_get_string(
    zx_vmar_map(cvmar, ZX_VM_PERM_READ | ZX_VM_PERM_WRITE | ZX_VM_PERM_EXECUTE, (size_t) 0, cmem, 0, child_mem_size,
                &child_entry)));
  size_t fptrs[2] = {
    vdso_addr + ((void *) zx_debug_write - vdso),
    vdso_addr + ((void *) zx_process_exit - vdso)
  };
  dlog("zx_vmo_write functions", "%s",
       zx_status_get_string(zx_vmo_write(cmem, fptrs, func_size, 2 * sizeof(size_t))));
  dlog("zx_process_start", "%s", zx_status_get_string(
    zx_process_start(child, cthread, (zx_vaddr_t) child_entry, (zx_vaddr_t) child_entry + child_mem_size - 16,
                     ZX_HANDLE_INVALID, child_entry + func_size)
  ));
  zx_nanosleep(zx_duration_from_min(10));
  dprintf("=============================\n");

  zx_process_exit(23);
}
