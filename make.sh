$FOUT/host_x64/zbi \
--type=cmdline --entry=userboot=bin/init --prefix= --files EMPTY \
--type=cmdline --entry=kernel.bypass-debuglog=true --prefix= --files EMPTY \
--type=cmdline --entry=kernel.enable-serial-syscalls=true --prefix= --files EMPTY \
--type=cmdline --entry=kernel.halt-on-panic=true --prefix= --files EMPTY \
--type=cmdline --entry=kernel.root-job.behavior=halt --prefix= --files EMPTY \
--type=cmdline --entry=TERM=screen-256color --prefix= --files EMPTY \
--type=cmdline --entry=kernel.serial=legacy --prefix= --files EMPTY \
--type=cmdline --entry=kernel.entropy-mixin=0000000000000000000000000000000000000000000000000000000000000000 --prefix= --files EMPTY \
--type=container $FOUT/kernel_x64/kernel.zbi --prefix= --files custom_bootfs.fini --output out/custom.zbi --bootable=x64 --compressed=zstd
