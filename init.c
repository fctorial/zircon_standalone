#include <libs/procargs/processargs.h>
#include <libs/utils/stdlib.h>
#include <libs/utils/zk.h>
#include <libs/linker/linker.h>

void child_init(zx_handle_t _, void *vdso) {
  char msg[5];
  msg[0] = 'm';
  msg[1] = 'a';
  msg[2] = 'm';
  msg[3] = 'a';
  msg[4] = '\n';
  typeof(zx_debug_write) write = (typeof(zx_debug_write)) vdso - 0x7000 + 0x7ba7;
  typeof(zx_process_exit) exit = (typeof(zx_process_exit)) vdso - 0x7000 + 0x7eae;
  write(msg, 5);
  exit(22);
}

void init(zx_handle_t chan, void *vdso) {
  link(vdso);

  dprintf("=============================\n");
  handles_container_t handles;
  memset(&handles, 0, sizeof(handles));
  extract_handles_chan(chan, &handles);
  zx_handle_close(handles.ldsvc);

  size_t vdso_size = 0;
  zx_status_t status;
  status = zx_vmo_get_size(handles.vmo_vdso, &vdso_size);
  if (status != ZX_OK) {
    dlog("vdso size fetch failed", "%s", zx_status_get_string(status));
  } else {
    dlog("vdso size", "%d", vdso_size);
  }

  const size_t child_mem_size = 8 * 1024;
  zx_handle_t child, cvmar, cthread, cmem, cvdso;
  dlog("zx_process_create", "%s",
       zx_status_get_string(zx_process_create(handles.job_default, "child", 5, 0, &child, &cvmar)));
  dlog("zx_thread_create", "%s", zx_status_get_string(zx_thread_create(child, "child_thread", 12, 0, &cthread)));
  size_t vdso_addr;
  dlog("zx_vmar_map vdso", "%s", zx_status_get_string(
    zx_vmar_map(cvmar, ZX_VM_PERM_READ | ZX_VM_PERM_EXECUTE, (size_t) 0, handles.vmo_vdso, 0x7000, vdso_size - 0x7000, &vdso_addr)));
  dlog("zx_vmo_create cmem", "%s", zx_status_get_string(zx_vmo_create(child_mem_size, 0, &cmem)));
  dlog("zx_vmo_replace_as_executable cmem", "%s",
       zx_status_get_string(zx_vmo_replace_as_executable(cmem, ZX_HANDLE_INVALID, &cmem)));
  int func_size = 512;
  dlog("zx_vmo_write executable", "%s", zx_status_get_string(zx_vmo_write(cmem, child_init, 0, func_size)));
  size_t child_entry;
  dlog("zx_vmar_map", "%s", zx_status_get_string(
    zx_vmar_map(cvmar, ZX_VM_PERM_READ | ZX_VM_PERM_WRITE | ZX_VM_PERM_EXECUTE, (size_t) 0, cmem, 0, child_mem_size,
                &child_entry)));
  dlog("cmem addr", "%p", child_entry);
  dlog("vdso addr", "%p", vdso_addr);
  dlog("zx_process_start", "%s", zx_status_get_string(
    zx_process_start(child, cthread, (zx_vaddr_t) child_entry, (zx_vaddr_t) child_entry + child_mem_size - 16,
                     ZX_HANDLE_INVALID, vdso_addr)
  ));
  zx_object_wait_one(child, ZX_PROCESS_TERMINATED, ZX_TIME_INFINITE, NULL);
  struct zx_info_process info;
  zx_object_get_info(child, ZX_INFO_PROCESS, &info, sizeof(info), NULL, NULL);
  dprintf("=============================\n");

  zx_process_exit(info.return_code);
}
