CC=clang

all: out/custom.zbi Makefile

out/linker: build/gen_linker.js ${FOUT}/gen/zircon/vdso/zx.fidl.json
	node build/gen_linker.js
	touch out/linker

out/init: init.c out/linker Makefile
	${CC} -ggdb -fno-stack-protector \
	    -Wno-attributes \
	    -I../zircon/system/public -Ibuild \
	    -I${FOUT}/gen/include \
	    -static -nostdlib -fPIC -fPIE -Wl,--entry=init \
	    -o out/init init.c lib.c out/linker.c
	elfedit --output-type dyn out/init

out/custom.zbi: build/make.sh out/init build/custom_bootfs.fini ${FOUT}/kernel_x64/kernel.zbi ${FOUT}/multiboot.bin Makefile
	./build/make.sh

clean:
	rm -fr out/*

out/test: test.c init.c Makefile
	${CC} -ggdb \
        -I../zircon/system/public \
        test.c init.c lib.c -o out/test
