CMD="$FUCHSIA_OUT/host_x64/zbi"
for c in `cat build/config/cmdline.txt`; do
  CMD="$CMD --type=cmdline --entry=$c --prefix= --files build/EMPTY"
done

CMD="$CMD --type=container $FUCHSIA_OUT/$([ -n "$TARGET_IS_ARM" ] && echo kernel_arm64 || echo kernel_x64)/kernel.zbi --prefix= --files build/config/bootfs.fini --output out/custom.zbi --compressed=zstd"

$CMD
