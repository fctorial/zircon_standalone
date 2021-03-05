ENTRY(_start)
SECTIONS
{
    . = 0x100000;
    .h : {
        . += 0x100;
    } :headers
    .text : {
        *(.text*)
    } :text
    .data : {
        *(.data*)
    } :data
    .rodata : {
        *(.rodata*)
    } :rodata
    .bss : {
        *(.bss*)
    } :bss
}

PHDRS
{
    headers PT_LOAD FILEHDR PHDRS ;
    text PT_LOAD ;
    data PT_LOAD ;
    rodata PT_LOAD ;
    bss PT_LOAD ;
}
