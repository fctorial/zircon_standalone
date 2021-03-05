CC=../prebuilt/third_party/clang/linux-x64/bin/clang

all: out/custom.zbi Makefile

out/init: init.c Makefile libs
	${CC} -ggdb -fno-stack-protector \
	    -Wno-attributes \
	    -I../zircon/system/public -I. \
	    -static -nostdlib -fPIC -fPIE -Wl,--entry=init \
	    -o out/init init.c libs/utils/stdlib.c libs/procargs/processargs.c libs/linker/linker.c
	elfedit --output-type dyn out/init

out/custom.zbi: build/make.sh out/init build/custom_bootfs.fini ${FOUT}/kernel_x64/kernel.zbi ${FOUT}/multiboot.bin Makefile
	./build/make.sh

clean:
	rm -fr out/*

out/linker: build/gen_linker.js
	node build/gen_linker.js
	touch out/linker

libs/headers/syscall_signatures.h: FORCE
	gcc -I../zircon/system/public -I${FOUT}/gen/include build/syscalls_extractor.h -E -o libs/headers/syscall_signatures.h
	sed -i -e '/^#/d' libs/headers/syscall_signatures.h

FORCE:
