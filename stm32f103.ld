

ENTRY(Reset_Handler)
_Min_Stack_Size = 0x400;



MEMORY 
{
    FLASH   (rx)    : ORIGIN = 0x08000000, LENGTH = 64K
    RAM     (rwx)   : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .isr_vector : {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH
    
    .text : {
        . = ALIGN(4);
        *(.text .text.*)
        *(.rodata .rodata*)
        . = ALIGN(4);
    } > FLASH

    .data : {
        . = ALIGN(4);
        _sdata = .;
        *(.data .data.*)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT> FLASH

    _sidata = LOADADDR(.data);

    .bss : {
        . = ALIGN(4);
        _sbss = .;
        *(.bss .bss.*)
        . = ALIGN(4);
        _ebss = .;
    } > RAM

    .stack_check : {
        . = ALIGN(8);
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } > RAM

    _estack = ORIGIN(RAM) + LENGTH(RAM);
}
