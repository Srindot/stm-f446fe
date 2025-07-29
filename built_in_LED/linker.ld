/*
 * linker.ld
 *
 * Linker script for the STM32F446RE microcontroller.
 * Defines memory regions and section placements.
 */

/* Define the memory layout */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Define a symbol for the end of the stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Define the sections */
SECTIONS
{
  /* The .isr_vector section goes first at the beginning of FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Keep the vector table */
    . = ALIGN(4);
  } >FLASH

  /* The .text section contains the program code */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections */
    *(.rodata)         /* .rodata sections (read-only data) */
    *(.rodata*)        /* .rodata* sections */
    . = ALIGN(4);
    _etext = .;        /* Define a symbol for the end of the code */
  } >FLASH

  /* The .data section contains initialized data */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* Define a symbol for the start of data */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    . = ALIGN(4);
    _edata = .;        /* Define a symbol for the end of data */
  } >RAM AT> FLASH     /* This section is loaded into RAM but stored in FLASH */

  /* The .bss section contains uninitialized data */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;         /* Define a symbol for the start of bss */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;         /* Define a symbol for the end of bss */
    __bss_end__ = _ebss;
  } >RAM

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
