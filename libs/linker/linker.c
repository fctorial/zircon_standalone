#include <libs/utils/stdlib.h>
#include <build/elf.h>
#include "linker.h"

typedef struct {
  void *vdso;
  char *names;
  Elf64_Sym *syms;
} lib_info_t;

bool parse_lib(void *lib, lib_info_t *res) {
  Elf64_Ehdr *header = lib;
  int ph_idx;
  Elf64_Phdr *ph;
  for (ph_idx = 0; ph_idx < header->e_phnum; ph_idx++) {
    ph = lib + header->e_phoff + ph_idx * header->e_phentsize;
    if (ph->p_type == PT_DYNAMIC) {
      break;
    }
  }
  if (ph_idx == header->e_phnum) {
    return false;
  }

  memset(res, 0, sizeof(lib_info_t));
  res->vdso = lib;
  size_t dt_count = ph->p_filesz / sizeof(Elf64_Dyn);
  for (size_t i = 0; i < dt_count; i++) {
    Elf64_Dyn* dt = lib + ph->p_offset + i * sizeof(Elf64_Dyn);
    if (dt->d_tag == DT_STRTAB) {
      res->names = lib + dt->d_un.d_ptr;
    } else if (dt->d_tag == DT_SYMTAB) {
      res->syms = lib + dt->d_un.d_ptr;
    }
  }

  if (res->names == 0 || res->syms == 0) {
    return false;
  }
  return true;
}

void *find_func(lib_info_t *vi, char *name) {
  for (Elf64_Sym* sym = vi->syms + 1; sym->st_info != 0; sym++) {
    if (strcmp(vi->names + sym->st_name, name) == 0) {
      return vi->vdso + sym->st_value;
    }
  }
  return NULL;
}

#define SYSCALL(name) typeof(_##name)* name;
#include "syscalls.inc"
#undef SYSCALL

void link(void* vdso) {
  lib_info_t vi;
  parse_lib(vdso, &vi);
#define SYSCALL(name) name = find_func(&vi, #name);
#include "syscalls.inc"
#undef SYSCALL
}
