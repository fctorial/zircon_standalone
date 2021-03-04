CC=clang

all: build/custom.zbi Makefile

build/linker: gen_linker.js ${FOUT}/gen/zircon/vdso/zx.fidl.json
	node gen_linker.js
	touch build/linker

build/init: init.c build/linker Makefile
	${CC} -ggdb -fno-stack-protector \
	    -Wno-attributes \
	    -I../zircon/system/public \
	    -I${FOUT}/gen/include \
	    -static -nostdlib -fPIC -fPIE -Wl,--entry=init \
	    -o build/init init.c lib.c build/linker.c
	elfedit --output-type dyn build/init

build/custom.zbi: make.sh build/init custom_bootfs.fini ${FOUT}/kernel_x64/kernel.zbi ${FOUT}/multiboot.bin Makefile
	./make.sh

clean:
	rm -fr build/*

build/test: test.c init.c Makefile
	${CC} -ggdb \
        -I../zircon/system/public \
        test.c init.c lib.c -o build/test
