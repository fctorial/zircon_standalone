CC=clang

all: custom.zbi Makefile

init: init.c Makefile
	${CC} -ggdb -fno-stack-protector \
	    -I../zircon/system/public \
	    -static -nostdlib -fPIC -fPIE -Wl,--entry=init \
	    -o build/init init.c lib.c
	elfedit --output-type dyn build/init

custom.zbi: make.sh init custom_bootfs.fini ${FOUT}/kernel_x64/kernel.zbi ${FOUT}/multiboot.bin Makefile
	./make.sh

clean:
	rm -fr build/*

test: test.c init.c Makefile
	${CC} -ggdb \
        -I../zircon/system/public \
        test.c init.c lib.c -o test
