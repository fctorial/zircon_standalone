CC=../prebuilt/third_party/clang/linux-x64/bin/clang

all: out/custom.zbi Makefile

out/linker: build/gen_linker.js
	node build/gen_linker.js
	touch out/linker

out/init: init.c libs/procargs/processargs.c libs/procargs/processargs.h libs/utils/stdlib.c libs/utils/stdlib.h out/linker Makefile
	${CC} -ggdb -fno-stack-protector \
	    -Wno-attributes \
	    -I../zircon/system/public -I${FOUT}/gen/include -I. \
	    -static -nostdlib -fPIC -fPIE -Wl,--entry=init \
	    -o out/init init.c libs/utils/stdlib.c libs/procargs/processargs.c out/linker.c
	elfedit --output-type dyn out/init

out/custom.zbi: build/make.sh out/init build/custom_bootfs.fini ${FOUT}/kernel_x64/kernel.zbi ${FOUT}/multiboot.bin Makefile
	./build/make.sh

clean:
	rm -fr out/*

out/test: test.c init.c Makefile
	${CC} -ggdb \
        -I../zircon/system/public \
        test.c init.c lib.c -o out/test
