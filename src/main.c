/**
  ******************************************************************************
  * @file    main.c
  * @author  3S0
  * @version V1.0
  * @date    21/09/2016
  * @brief   Example project.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "aula_1.h""
#include "aula_2.h"

/* @PT
 * main.c: cofigura o GPIOA5 como saída e activa-a (ligando o LED da placa)
 * Abrir o ficheiro RM0008  - Reference Manual do STM32F103xx.
 * A página 170 explica o MODE e CNF de cada GPIO.
 * Validar esta configuraçao usando a perspectiva de Debug do eclipse (AC6)
 * Run->Debug; Run-> Resume; Run->Suspend;
 * Duplo click no GPIOA na janela I/O Register para obter os valores do micro.
 *
 * @EN
 * main.c: Configures GPIOA5 as an output and activate it (turns on the LED in the board)
 * Open the file RM0008 - STM32F103xx Reference Manual.
 * The page 170 explains the MODE and CNF for each GPIO.
 * Validate this configuration using the eclipse's debug perspective (AC6)
 * Run->Debug; Run-> Resume; Run->Suspend;
 * Double-click on GPIOA in the I/O Register Window to fetch the values from the micro.
 *
 * */


int main(void)
{
    /* Enable GPIOA clock */
//    RCC->APB2ENR = 0x00000004;
//
//    /* GPIOA5 CNF: General Purpose Output push-pull  */
//    GPIOA->CRL &= ~0x00C00000;
//
//    /* GPIOA5 MODE: Output mode, max speed 50 MHz */
//    GPIOA->CRL |= 0x00300000;
//
//    /* Set GPIOA5 */
//    GPIOA->BSRR = 0x00000020;

    /* Reset GPIOA5 */
    //GPIOA->BSRR = 0x00200000;  //or GPIOA->BRR = 0x00000020;

	//RCC Init
	aula_2_Init(HSE_PLL_MAX);
	//GPIO Initializations
	aula_1_Init();

    /* Infinite loop */
    for(;;)
    {
    	//Toggle do LED
    	aula_2_Action();
    }
    return 0;
}

