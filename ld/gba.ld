ENTRY(_start)

MEMORY {
  ROM   (rx) : ORIGIN = 0x08000000, LENGTH = 32M
  IWRAM (rx) : ORIGIN = 0x03000000, LENGTH = 32K
  EWRAM (rx) : ORIGIN = 0x02000000, LENGTH = 256K
}

__ewram_start = ORIGIN(EWRAM);
__ewram_end   = ORIGIN(EWRAM) + LENGTH(EWRAM);
__iwram_start = ORIGIN(IWRAM);
__iwram_end   = ORIGIN(IWRAM) + LENGTH(IWRAM);
__sp_irq      = __iwram_end - 160;
__sp_sys      = __iwram_end - 256;

SECTIONS {
  .text : 
  {
    _start = .;
    *(.text*)
    *(.rodata*)
    _etext = .;
  } > ROM

  .data : AT(_etext)
  {
    _sdata = .;
    *(.data*)
    _edata = .;
  } > IWRAM

  .bss :
  {
    _sbss = .;
    *(.bss)
    _ebss = .;
  } > IWRAM
}
