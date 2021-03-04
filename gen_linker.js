const fs = require('fs')

const exclusions = [
  'zx_status_get_string',
  'zx_exception_get_string',
  'zx_system_get_version'
]

const reg = /(WEAK_FUNCTION)\((\w+), (\w+), \w+\)/
async function main() {
  const lines = fs.readFileSync('/home/fctorial/src/fuchsia/fuchsia/out/bringup.qemu-x64/userboot_x64/gen/zircon/kernel/lib/userabi/userboot/vdso-syms.h').toString().split('\n').filter(e => e !== '')
  const syscalls = lines.map(line => {
    const m = reg.exec(line)
    if (m) {
      return {
        name: m[2],
        addr: m[3]
      }
    }
  }).filter(e => e)
    .filter(syscall => syscall.name.indexOf('test') === -1)
    .filter(syscall => exclusions.indexOf(syscall.name) === -1)
  const linker_h = [
    '#include "../syscalls.h"',
    '',
    'void link_dependent(void*);'
  ]
  syscalls.forEach(syscall => linker_h.push(`extern typeof(_${syscall.name})* ${syscall.name};`))

  const linker_c = [
    `#include "linker.h"`
  ]
  linker_c.push(``)
  syscalls.forEach(syscall => linker_c.push(`typeof(_${syscall.name})* ${syscall.name};`))
  linker_c.push(``)
  linker_c.push(`void link_dependent(void* vdso) {`)
  syscalls.forEach(syscall => linker_c.push(`\t${syscall.name} = vdso + ${syscall.addr};`))
  linker_c.push(`}`)
  fs.writeFileSync('out/linker.h', linker_h.join('\n'))
  fs.writeFileSync('out/linker.c', linker_c.join('\n'))
}

if (require.main === module) {
  main()
    .then(() => process.exit(0))
}
