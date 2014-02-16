/*==================================================================================================

	stm32f4_linker.h
	
	This file contains linker definitions which may be used along the application code, such as
	binary section addresses.

 ===================================================================================================

	Author: Henrique Persico Rossi
	e-mail: henriqueprossi@gmail.com

 =================================================================================================*/

#ifndef _STM32F4_LINKER_H_
#define _STM32F4_LINKER_H_

/*==================================================================================================
  INCLUDE FILES
==================================================================================================*/


/*==================================================================================================
  GLOBAL DEFINITIONS
==================================================================================================*/


/*==================================================================================================
  GLOBAL TYPEDEFS
==================================================================================================*/


/*==================================================================================================
  GLOBAL VARIABLES
==================================================================================================*/

extern unsigned long _stack_start;  /* Start of the STACK memory. */
extern unsigned long _stack_end;    /* End of the STACK memory. */
extern unsigned long _heap_start;   /* Start of the HEAP memory. */
extern unsigned long _heap_end;     /* End of the HEAP memory (one byte past the last byte of this memory). */
extern unsigned long _sidata;       /* Start address for the contents initialization of the .data
                                       section. defined in linker script. */
extern unsigned long _sdata;        /* Start address for the .data section, defined in linker script */
extern unsigned long _edata;        /* End address for the .data section, defined in linker script. */
extern unsigned long _sbss;         /* Start address for the .bss section, defined in linker script. */
extern unsigned long _ebss;         /* End address for the .bss section, defined in linker script. */
extern unsigned long _end;          /* Start address of the heap memory, defined in linker script. */

/*==================================================================================================
  GLOBAL FUNCTIONS
==================================================================================================*/

#endif /* _STM32F4_LINKER_H_ */

