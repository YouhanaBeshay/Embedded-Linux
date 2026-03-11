ENTRY(_start)

SECTIONS
{
    /* address that we will put the application in (inside the u-boot) */
    . = 0x80000;
    __start = .;

    .text :
    {
        KEEP(*(.text.boot))
        *(.text*)
    }
    .rodata :
    {
        *(.rodata*)
    }

    .data :
    {
        *(.data*)
    }

    __bss_start = .;
    .bss :
    {
        *(.bss*)
    }
    __bss_end = .;




    __end = .;

    __size_of_map = __end - __start;

    __size_of_bss = __bss_end - __bss_start;
}