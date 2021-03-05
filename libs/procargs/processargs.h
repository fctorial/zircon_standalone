// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYSROOT_ZIRCON_PROCESSARGS_H_
#define SYSROOT_ZIRCON_PROCESSARGS_H_

#include <stdint.h>
#include <zircon/compiler.h>
#include <zircon/types.h>

__BEGIN_CDECLS

// This is a protocol for passing state to a new process
// via a message in a channel.

#define ZX_PROCARGS_PROTOCOL ((uint32_t)0x4150585du)  // MXPA
#define ZX_PROCARGS_VERSION ((uint32_t)0x0001000u)

typedef struct zx_proc_args zx_proc_args_t;


struct zx_proc_args {
  // Protocol and version identifiers to allow for
  // different process start message protocols and
  // versioning of the same.
  uint32_t protocol;
  uint32_t version;

  // Offset from start of message to handle info
  // array, which contains one uint32_t per handle
  // passed along with the message.
  uint32_t handle_info_off;

  // Offset from start of message to arguments and
  // count of arguments.  Arguments are provided as
  // a set of null-terminated utf-8 strings, one
  // after the other.
  uint32_t args_off;
  uint32_t args_num;

  // Offset from start of message to environment strings and count of
  // them.  Environment entries are provided as a set of null-terminated
  // UTF-8 strings, one after the other.  Canonically each string has
  // the form "NAME=VALUE", but nothing enforces this.
  uint32_t environ_off;
  uint32_t environ_num;

  // Offset from start of message to name strings and count of them.
  // These strings are packed similar to the argument strings,
  // but are referenced by PA_NS_* handle table entries and used
  // to set up namespaces.
  //
  // Specifically: In a handle table entry with PA_HND_TYPE(info)
  // of PA_NS_*, PA_HND_ARG(info) is an index into this name table.
  uint32_t names_off;
  uint32_t names_num;
};

typedef struct {
  zx_handle_t proc_self;
  zx_handle_t thread_self;
  zx_handle_t job_default;
  zx_handle_t vmar_root;
  zx_handle_t vmo_vdso;
  zx_handle_t vmo_stack;
  zx_handle_t vmo_executable;
  zx_handle_t vmo_zbi;
  zx_handle_t vmo_bootfs;
  zx_handle_t vmo_kernel_file;
  zx_handle_t clock_utc;
  zx_handle_t mmio;
  zx_handle_t irq;
  zx_handle_t ioport;
  zx_handle_t smc;
  zx_handle_t sys;
  zx_handle_t res_;
} handles_container_t;

// Handle Info entries associate a type and optional
// argument with each handle included in the process
// arguments message.
#define PA_HND(type, arg) (((type)&0xFF) | (((arg)&0xFFFF) << 16))
#define PA_HND_TYPE(n) ((n)&0xFF)
#define PA_HND_ARG(n) (((n) >> 16) & 0xFFFF)

// --- Core Runtime Handles ---
// Used by libc init (or equivalent) and dynamic loader

// Handle to our own process.
#define PA_PROC_SELF 0x01u

// Handle to the initial thread of our own process.
#define PA_THREAD_SELF 0x02u

// Handle to a job object which can be used to make child processes.
//
// The job can be the same as the one used to create this process or it can
// be different.
#define PA_JOB_DEFAULT 0x03u

// Handle to the root of our address space
#define PA_VMAR_ROOT 0x04u

// Handle to the VMAR used to load the initial program image.
#define PA_VMAR_LOADED 0x05u

// --- Loader Service and VMO Handles ---
// Used by libc init (or equivalent) and dynamic loader

// Service for loading shared libraries.
//
// See |fuchsia.ldsvc.Loader| for the interface definition.
#define PA_LDSVC_LOADER 0x10u

// Handle to the VMO containing the ELF image of the system vDSO.  This
// handle is duplicable, transferable, readable, and executable, but not
// writable.  The contents of the VM object should be treated like any
// other general-purpose ELF file image of type ET_DYN.  A process only
// needs this handle so that it can map the vDSO into new processes it
// might create or propagate it on to its children so they can do so.
// Each process's own vDSO was mapped in by its creator before the
// process started, its address passed as an argument to entry point.
#define PA_VMO_VDSO 0x11u

// Handle to the VMO used to map the initial thread's stack.  This
// handle usually has all rights.  The protocol between process creator
// and new process is that this entire VM object has been mapped in
// before the process starts.  The initial value for the SP register in
// the new process is the high edge of the mapping (assuming stacks grow
// downwards), adjusted down as required by the particular machine's C
// calling convention for function entry.  Thus the new process can
// compute its exact stack bounds by subtracting the size reported by
// this VMO from the (adjusted back up) initial SP value.
#define PA_VMO_STACK 0x13u

// VM object handle for the main executable file
#define PA_VMO_EXECUTABLE 0x14u

// Used by kernel and userboot during startup
#define PA_VMO_BOOTDATA 0x1Au

// Used by kernel and userboot during startup
#define PA_VMO_BOOTFS 0x1Bu

// Used by the kernel to export debug information as a file in bootfs.  When
// devmgr starts, it looks for handles of this type, and adds them as files in
// /boot/kernel/<vmo-name>.
#define PA_VMO_KERNEL_FILE 0x1Cu

// --- Namespace Handles ---

// A handle which will handle OPEN requests relative
// to a particular path which is specified by the
// nametable entry referred to by the "arg" field
#define PA_NS_DIR 0x20u

// --- File Descriptor Handles ---

// A handle which will be used as a file descriptor.
#define PA_FD 0x30u

// -- Lifecyle handle --
//
// A Handle to a channel on which the process may receive lifecycle events from
// the ELF runner by serving the |fuchsia.process.Lifecycle| protocol.
#define PA_LIFECYCLE 0x3Au

// Server endpoint for handling connection to appmgr services.
#define PA_DIRECTORY_REQUEST 0x3Bu

// Used by devmgr and devhosts
#define PA_RESOURCE 0x3Fu

// --- Clock handles ---
//
// A clock which provides access to UTC.  Used by runtimes which are expected to
// provide access to UTC via their standard libraries.
//
#define PA_CLOCK_UTC 0x40u

// --- Resource handles ---
#define PA_MMIO_RESOURCE 0x50
#define PA_IRQ_RESOURCE 0x51
#define PA_IOPORT_RESOURCE 0x52
#define PA_SMC_RESOURCE 0x53
#define PA_SYSTEM_RESOURCE 0x54

// --- Various ---

// Handle types for one-off use and prototyping
#define PA_USER0 0xF0u
#define PA_USER1 0xF1u
#define PA_USER2 0xF2u

__END_CDECLS

// Examine the next message to be read from the channel, and yield
// the data size and number of handles in that message.
zx_status_t processargs_message_size(zx_handle_t channel, uint32_t *nbytes, uint32_t *nhandles);

// Define a properly-aligned buffer on the stack for reading a
// processargs message.  The nbytes parameter should be gotten from
// processargs_message_size.
#define PROCESSARGS_BUFFER(variable, nbytes) alignas(zx_proc_args_t) uint8_t variable[nbytes]

// The buffer provided must be properly aligned (alignas(zx_proc_args_t))
// and large enough for the message pending on the given bootstrap
// message-pipe handle.  This reads the message into that buffer, validates
// the message format of, and yields pointers into the buffer for the
// header and the handle-info array.
zx_status_t processargs_read(zx_handle_t bootstrap, void *buffer, uint32_t nbytes,
                             zx_handle_t handles[], uint32_t nhandles, zx_proc_args_t **pargs,
                             uint32_t **handle_info);

// Extract known handle types from the handles.
void processargs_extract_handles(uint32_t nhandles, const zx_handle_t handles[], const uint32_t handle_info[],
                                 handles_container_t *);

void extract_handles_chan(zx_handle_t chan, handles_container_t* handles_container);

// This assumes processargs_read has already succeeded on the same
// buffer.  It unpacks the argument and environment strings into arrays
// provided by the caller.  If not NULL, the argv[] array must have
// zx_proc_args_t.args_num + 1 elements.  If not NULL, the envp[] array
// must have zx_proc_args_t.environ_num + 1 elements.  If not NULL, the
// names[] array must have zx_proc_args_t.names_num + 1 elements. The
// last element of each array is filled with a NULL pointer.
zx_status_t processargs_strings(void *msg, uint32_t bytes, char *argv[], char *envp[],
                                char *names[]);

#endif  // SYSROOT_ZIRCON_PROCESSARGS_H_
