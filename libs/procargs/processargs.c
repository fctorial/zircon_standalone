// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "processargs.h"
#include <libs/linker/linker.h>

#define MALFORMED ZX_ERR_INVALID_ARGS

zx_status_t processargs_message_size(zx_handle_t channel, uint32_t* nbytes, uint32_t* nhandles) {
  zx_status_t status = zx_channel_read(channel, 0, NULL, NULL, 0, 0, nbytes, nhandles);
  if (status == ZX_ERR_BUFFER_TOO_SMALL)
    status = ZX_OK;
  return status;
}

zx_status_t processargs_read(zx_handle_t bootstrap, void* buffer, uint32_t nbytes,
                             zx_handle_t handles[], uint32_t nhandles, zx_proc_args_t** pargs,
                             uint32_t** handle_info) {
  if (nbytes < sizeof(zx_proc_args_t))
    return ZX_ERR_INVALID_ARGS;
  if ((uintptr_t)buffer % _Alignof(zx_proc_args_t) != 0)
    return ZX_ERR_INVALID_ARGS;

  uint32_t got_bytes = 0;
  uint32_t got_handles = 0;
  zx_status_t status =
    zx_channel_read(bootstrap, 0, buffer, handles, nbytes, nhandles, &got_bytes, &got_handles);
  if (status != ZX_OK)
    return status;
  if (got_bytes != nbytes || got_handles != nhandles)
    return ZX_ERR_INVALID_ARGS;

  zx_proc_args_t* const pa = buffer;

  if (pa->protocol != ZX_PROCARGS_PROTOCOL || pa->version != ZX_PROCARGS_VERSION)
    return MALFORMED;

  if (pa->handle_info_off < sizeof(*pa) || pa->handle_info_off % _Alignof(uint32_t) != 0 ||
      pa->handle_info_off > nbytes || (nbytes - pa->handle_info_off) / sizeof(uint32_t) < nhandles)
    return MALFORMED;

  if (pa->args_num > 0 && (pa->args_off < sizeof(*pa) || pa->args_off > nbytes ||
                           (nbytes - pa->args_off) < pa->args_num))
    return MALFORMED;

  if (pa->environ_num > 0 && (pa->environ_off < sizeof(*pa) || pa->environ_off > nbytes ||
                              (nbytes - pa->environ_off) < pa->environ_num))
    return MALFORMED;

  *pargs = pa;
  *handle_info = (void*)&((uint8_t*)buffer)[pa->handle_info_off];
  return ZX_OK;
}

void processargs_extract_handles(uint32_t nhandles, const zx_handle_t handles[], const uint32_t handle_info[], handles_container_t* handles_container) {
  for (uint32_t i = 0; i < nhandles; ++i) {
#define ASSIGN(type, field) case type: handles_container->field = handles[i]; break;
    switch (PA_HND_TYPE(handle_info[i])) {
      ASSIGN(PA_PROC_SELF, proc_self)
      ASSIGN(PA_JOB_DEFAULT, job_self)
      ASSIGN(PA_VMAR_ROOT, vmar_root)
      ASSIGN(PA_THREAD_SELF, thread_self)
      ASSIGN(PA_CLOCK_UTC, clock_utc)
      ASSIGN(PA_VMO_VDSO, vmo_vdso)
      ASSIGN(PA_VMO_STACK, vmo_stack)
      ASSIGN(PA_VMO_EXECUTABLE, vmo_executable)
      ASSIGN(PA_VMO_BOOTDATA, vmo_zbi)
      ASSIGN(PA_VMO_BOOTFS, vmo_bootfs)
      ASSIGN(PA_VMO_KERNEL_FILE, vmo_kernel_file)
      ASSIGN(PA_MMIO_RESOURCE, mmio)
      ASSIGN(PA_IRQ_RESOURCE, irq)
      ASSIGN(PA_IOPORT_RESOURCE, ioport)
      ASSIGN(PA_SMC_RESOURCE, smc)
      ASSIGN(PA_SYSTEM_RESOURCE, sys)
      ASSIGN(PA_RESOURCE, res_)
    }
  }
#undef ASSIGN
}

void extract_handles_chan(zx_handle_t chan, handles_container_t* handles_container) {
  uint32_t bsc, hsc;
  processargs_message_size(chan, &bsc, &hsc);

  char bs[bsc];
  zx_handle_t hs[hsc];
  struct zx_proc_args* args;
  uint32_t* handle_infos;
  processargs_read(chan, bs, bsc, hs, hsc, &args, &handle_infos);

  processargs_extract_handles(hsc, hs, handle_infos, handles_container);
}

static zx_status_t unpack_strings(char* buffer, uint32_t bytes, char* result[], uint32_t off,
                                  uint32_t num) {
  char* p = &buffer[off];
  for (uint32_t i = 0; i < num; ++i) {
    result[i] = p;
    do {
      if (p >= &buffer[bytes])
        return MALFORMED;
    } while (*p++ != '\0');
  }
  result[num] = NULL;
  return ZX_OK;
}

zx_status_t processargs_strings(void* msg, uint32_t bytes, char* argv[], char* envp[],
                                char* names[]) {
  zx_proc_args_t* const pa = msg;
  zx_status_t status = ZX_OK;
  if (argv != NULL) {
    status = unpack_strings(msg, bytes, argv, pa->args_off, pa->args_num);
  }
  if (envp != NULL && status == ZX_OK) {
    status = unpack_strings(msg, bytes, envp, pa->environ_off, pa->environ_num);
  }
  if (names != NULL && status == ZX_OK) {
    status = unpack_strings(msg, bytes, names, pa->names_off, pa->names_num);
  }
  return status;
}
