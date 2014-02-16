/*==================================================================================================

  hello_world.c

  Used hardware: STM32F4 - Discovery evaluation board

  ==================================================================================================

  Author: Henrique Persico Rossi
  e-mail: henriqueprossi@gmail.com

  ================================================================================================*/

/*==================================================================================================
  INCLUDE FILES
==================================================================================================*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*=================================================================================================
  LOCAL DEFINITIONS
=================================================================================================*/

/*==================================================================================================
  LOCAL FUNCTIONS
==================================================================================================*/

static void leds_blink_task(void * parameters);

/*==================================================================================================
  LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
  Function    : vApplicationIdleHook


  Description :

  Parameters  : None

  Returns     : None
==================================================================================================*/

void vApplicationIdleHook(void)
{

}

/*==================================================================================================
  Function    : vApplicationStackOverflowHook


  Description :

  Parameters  : None

  Returns     : None
==================================================================================================*/

void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName)
{

}

/*==================================================================================================
  Function    : vApplicationTickHook


  Description :

  Parameters  : None

  Returns     : None
==================================================================================================*/

void vApplicationTickHook(void)
{

}

/*==================================================================================================
  Function    : vApplicationMallocFailedHook


  Description :

  Parameters  : None

  Returns     : None
==================================================================================================*/

void vApplicationMallocFailedHook(void)
{

}

/*==================================================================================================
  Function    : main


  Description : Entry point of the user application. It only set/clear the LD3, LD4, LD5 and LD6 leds
                on the board.

  Parameters  : None

  Returns     : EXIT_SUCCESS:	Successful termination

                Otherwise:		Error
==================================================================================================*/

int main(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* At this point the microcontroller clock is already set, which is done through SystemInit()
   * function. This is done by means of the C runtime initialization (crt.c), which, afterwards,
   * call the main application.
   */

  /* Update SystemCoreClock variable according to Clock Register Values. The tick frequency is
   * set by the scheduler.
   */
  SystemCoreClockUpdate();

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  /* GPIOD Peripheral clock enable. */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   
  /* LED's configuration:
   * LD3: GPIO PD13 (0: OFF, 1: ON)
   * LD4: GPIO PD12 (0: OFF, 1: ON)
   * LD5: GPIO PD14 (0: OFF, 1: ON)
   * LD6: GPIO PD15 (0: OFF, 1: ON)
   */

  /* Configure PD12, PD13, PD14 and PD15 in output push-pull mode. */
  GPIO_InitStructure.GPIO_Pin   = LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  xTaskCreate(  leds_blink_task           ,
                "leds_blink_task"         ,
                configMINIMAL_STACK_SIZE  ,
                NULL                      ,
                tskIDLE_PRIORITY          ,
                NULL                      );

  /* it is started the scheduler. */
  vTaskStartScheduler();

  /* If all is well, the scheduler will now be running, and the following line will never be reached.
   * If the following line does execute, then there was insufficient FreeRTOS heap memory available
   * for the idle and/or timer tasks to be created.  See the memory management section on the
   * FreeRTOS web site for more details.
   */
  for (;;);
  
  return 0;
}

/*==================================================================================================
  Function    : leds_blink_task


  Description :

  Parameters  :

  Returns     :
==================================================================================================*/

static void leds_blink_task(void * parameters)
{
  for (;;) {
    GPIO_SetBits(GPIOD, LED4_PIN); /* LED4 ON */
    vTaskDelay(1000 / portTICK_RATE_MS);
    GPIO_SetBits(GPIOD, LED3_PIN); /* LED3 ON */
    vTaskDelay(1000 / portTICK_RATE_MS);
    GPIO_SetBits(GPIOD, LED5_PIN); /* LED5 ON */
    vTaskDelay(1000 / portTICK_RATE_MS);
    GPIO_SetBits(GPIOD, LED6_PIN); /* LED6 ON */
    vTaskDelay(1000 / portTICK_RATE_MS);
    GPIO_ResetBits(GPIOD, LED4_PIN | LED3_PIN | LED5_PIN | LED6_PIN);  /* All LEDs are OFF. */
    vTaskDelay(1000 / portTICK_RATE_MS);
  }
}
