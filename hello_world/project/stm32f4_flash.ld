/*==================================================================================================

	stm32f4_flash.ld
	
	linker script for STM32F4 - Code is run on the flash memory

 ===================================================================================================

	Author: Henrique Persico Rossi
	e-mail: henriqueprossi@gmail.com

 =================================================================================================*/

/* Describes the target system's memory map. */
MEMORY
{
  FLASH (rx)    : ORIGIN = 0x08000000, LENGTH = 1024K
  RAM (rwx)     : ORIGIN = 0x20000000, LENGTH = 112K + 16K
  CCM_RAM (rwx) : ORIGIN = 0x10000000, LENGTH = 64K
}

/* Generate a link error if heap and stack don't fit into RAM */
_heap_size  = 0x8000; /* required amount of heap  */
_stack_size = 0x1000; /* required amount of stack */

INCLUDE sections.ld
