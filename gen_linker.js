const fs = require('fs')
const vdso_info = require(process.env.FOUT + '/gen/zircon/vdso/zx.fidl.json')

async function main() {
  const syscalls = ['debug_write', 'process_exit', 'channel_read']
  // vdso_info.interface_declarations.map(
  //   dec => dec.methods.filter(m => !m.maybe_attributes.some(attr => attr.name === 'internal'))
  //     .map(m => m.name)
  //     .filter(name => name.indexOf('test') === -1)
  // )
  //   .forEach(names => syscalls.push(...names))

  const linker_h = [
    '#include <zircon/syscalls.h>',
    '',
    'void link_dependent(void*);'
  ]
  syscalls.forEach(syscall => linker_h.push(`extern typeof(zx_${syscall})* sys_${syscall};`))

  const linker_c = [
    `#include "linker.h"`,
    `#include "../../out/bringup.qemu-x64/kernel_x64/gen/zircon/kernel/lib/userabi/vdso-code.h"`
  ]
  linker_c.push(``)
  linker_c.push(``)
  syscalls.forEach(syscall => linker_c.push(`typeof(zx_${syscall})* sys_${syscall};`))
  linker_c.push(``)
  linker_c.push(``)
  linker_c.push(`void link_dependent(void* vdso) {`)
  syscalls.forEach(syscall => linker_c.push(`\tsys_${syscall} = vdso + VDSO_CODE_SYSCALL_zx_${syscall};`))
  linker_c.push(`}`)
  fs.writeFileSync('build/linker.h', linker_h.join('\n'))
  fs.writeFileSync('build/linker.c', linker_c.join('\n'))
}

if (require.main === module) {
  main()
    .then(() => process.exit(0))
}
