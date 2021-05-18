#include <libs/procargs/processargs.h>
#include <libs/utils/stdlib.h>
#include <libs/utils/zk.h>
#include <libs/linker/linker.h>

__attribute__((section("child_code"))) void child_init(zx_handle_t _, size_t *fns) {
  char msg[5];
  msg[0] = 'm';
  msg[1] = 'a';
  msg[2] = 'm';
  msg[3] = 'a';
  msg[4] = '\n';
  typeof(zx_debug_write) write = (typeof(zx_debug_write)) fns[0];
  typeof(zx_process_exit) exit = (typeof(zx_process_exit)) fns[1];
  exit(write(msg, 5));
}

size_t addr;
extern char __start_child_code;
extern char __stop_child_code;

void init(zx_handle_t chan, void *vdso) {
  link(vdso);

  dprintf("=============================\n");
  handles_container_t handles;
  memset(&handles, 0, sizeof(handles));
  extract_handles_chan(chan, &handles);

#define TRY(exp) {\
  zx_status_t status = exp; \
  if (status != ZX_OK) {    \
    dlog(zx_status_get_string(status), "%s", #exp);\
    goto end;\
  }\
}
  vdso_load_info vi;
  if (!get_vdso_load_info(handles.vmo_vdso, &vi)) {
    dprintf("couldn't parse vdso\n");
    goto end;
  }

  const size_t child_mem_size = 4 * 1024;
  size_t func_size = &__stop_child_code - &__start_child_code;
  zx_handle_t child, cvmar, vdso_vmar, cthread, cmem;

  TRY(zx_process_create(handles.job_default, "child", 5, 0, &child, &cvmar))
  TRY(zx_thread_create(child, "child_thread", 12, 0, &cthread))
  size_t vdso_addr;
  TRY(zx_vmar_allocate(cvmar, ZX_VM_CAN_MAP_SPECIFIC | ZX_VM_CAN_MAP_READ | ZX_VM_CAN_MAP_WRITE | ZX_VM_CAN_MAP_EXECUTE, 0, vi.exec_end, &vdso_vmar, &vdso_addr))
  TRY(zx_vmar_map(vdso_vmar, ZX_VM_PERM_READ | ZX_VM_SPECIFIC, (size_t) 0, handles.vmo_vdso, 0, vi.exec_start, &vdso_addr))
  TRY(zx_vmar_map(vdso_vmar, ZX_VM_PERM_READ | ZX_VM_PERM_EXECUTE | ZX_VM_SPECIFIC, vi.exec_start, handles.vmo_vdso, vi.exec_start, vi.exec_end - vi.exec_start, &addr))
  TRY(zx_vmo_create(child_mem_size, 0, &cmem))
  TRY(zx_vmo_replace_as_executable(cmem, ZX_HANDLE_INVALID, &cmem))
  TRY(zx_vmo_write(cmem, child_init, 0, func_size))
  size_t child_entry;
  TRY(zx_vmar_map(cvmar, ZX_VM_PERM_READ | ZX_VM_PERM_WRITE | ZX_VM_PERM_EXECUTE, (size_t) 0, cmem, 0, child_mem_size, &child_entry))
  size_t fptrs[2] = {
    vdso_addr + ((void*) zx_debug_write - vdso),
    vdso_addr + ((void*) zx_process_exit - vdso)
  };
  TRY(zx_vmo_write(cmem, fptrs, func_size, 2 * sizeof(size_t)))
  TRY(zx_process_start(child, cthread, (zx_vaddr_t) child_entry, (zx_vaddr_t) child_entry + child_mem_size - 16, ZX_HANDLE_INVALID, child_entry + func_size))
  zx_object_wait_one(child, ZX_PROCESS_TERMINATED, ZX_TIME_INFINITE, NULL);
  struct zx_info_process_v2 info;
  zx_object_get_info(child, ZX_INFO_PROCESS, &info, sizeof(info), NULL, NULL);

  end:
  dprintf("=============================\n");

  zx_process_exit(info.return_code);
#undef TRY
}
