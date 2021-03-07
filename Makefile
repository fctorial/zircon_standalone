CC=${FUCHSIA_DIR}/prebuilt/third_party/clang/linux-x64/bin/clang

SOURCES=init.c libs/utils/stdlib.c libs/procargs/processargs.c libs/linker/linker.c libs/utils/zk.c

all: out/custom.zbi Makefile

out/init: init.c libs Makefile ${SOURCES}
	${CC} -ggdb -O0 -fno-stack-protector \
	    -target $$([ -n "$$TARGET_IS_ARM" ] && echo aarch64-unknown-linux-gnu || echo x86_64-unknown-linux-gnu) \
	    -I${FUCHSIA_DIR}/zircon/system/public -I. \
	    -static -nostdlib -fPIE -Wl,--entry=init -Wl,-pie \
	    -o out/init ${SOURCES}
	elfedit --output-type dyn out/init

out/custom.zbi: build/make.sh out/init build/config ${FUCHSIA_OUT} Makefile
	./build/make.sh

clean:
	rm -fr out/*

out/linker: build/gen_linker.js
	node build/gen_linker.js
	touch out/linker

libs/headers/syscall_signatures.h: FORCE
	gcc -I${FUCHSIA_DIR}/zircon/system/public -I${FUCHSIA_OUT}/gen/include build/syscalls_extractor.h -E -o libs/headers/syscall_signatures.h
	sed -i -e '/^#/d' libs/headers/syscall_signatures.h

FORCE:
