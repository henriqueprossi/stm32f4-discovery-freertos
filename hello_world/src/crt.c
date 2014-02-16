/*==================================================================================================

  crt.c

  C Runtime initialization module

  ==================================================================================================

  Author: Henrique Persico Rossi
  e-mail: henriqueprossi@gmail.com

  =================================================================================================*/

/*==================================================================================================
  INCLUDE FILES
==================================================================================================*/

#include <stdint.h>
#include "project.h"
#include "crt.h"
#include "system_stm32f4xx.h"
#include "stm32f4_linker.h" /* Sections and symbols which are defined by the linker script */
#include "hello_world.h"    /* This is where the main function is declared */
#include <unistd.h>

/*==================================================================================================
  Function    : Reset_Handler

  Description : This function is used for C runtime initialization, which is the code that gets
                called when the processor first starts execution following a reset event. Only
                the absolutely necessary set is performed, which includes handling the .data and
                .bss segments, after which the application supplied main() routine is called.

  Parameters  : None

  Returns     : None
==================================================================================================*/

void Reset_Handler(void)
{
  uint32_t  * source;
  uint32_t  * dest;
  int         ret_main;

  /* Copy the initialized data of the ".data" segment from the FLASH to the area in the RAM. */
  source  = &_sidata;
  dest    = &_sdata;

  while (dest < &_edata) {
    *dest = *source;
    dest++;
    source++;
  }

  /* Clear the ".bss" segment */
  dest = &_sbss;

  while (dest < &_ebss) {
    *dest++ = 0;
  }

  /* Call the SystemInit code from CMSIS interface */
  SystemInit();

  /* The runtime environment is set. So, the main function is called */
  ret_main = main();
  (void) ret_main;

  /* If it is necessary handling any error status from main function, it may be done here. */
  for (;;) ;
}

#ifdef PROJ_IMPLEMMENT_SYSCALLS

/*==================================================================================================
  Function    : _sbrk

  Description : Increase program data space. As malloc and related functions depend on this, it is
                useful to have a working implementation. The following suffices for a standalone
                system; it exploits the symbol _end automatically defined by the GNU linker.

  Parameters  : incr  [IN]  The size in bytes of a new block of heap memory.

  Returns     : A pointer to a new block of available heap memory.
==================================================================================================*/

caddr_t _sbrk(int incr)
{
  static unsigned char  * heap = NULL;
  static unsigned char  * new_heap;
  unsigned char         * prev_heap_end;

  if (heap == NULL) {
    heap = (unsigned char *) &_end;
  }

  prev_heap_end = heap;
  new_heap = heap + incr;

  if ((new_heap > (unsigned char *) &_heap_end) || (new_heap < (unsigned char *) &_end)) {
    return NULL;
  }

  heap += incr;
  return (caddr_t) prev_heap_end;
}

#endif /* PROJ_IMPLEMMENT_SYSCALLS */
