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
	RCC_ConfigOptions Current_RCC_Option = L30MHZ;
	int numberOfRuns = 0;
	//GPIO Initializations
	aula_1_Init();
	//RCC Init
	aula_2_Init(Current_RCC_Option);

    /* Infinite loop */
    for(;;)
    {
    	numberOfRuns++;
    	//Toggle do LED
		aula_2_Action();
    	if(numberOfRuns == 10)
    	{
    		numberOfRuns = 0;
    		Current_RCC_Option = (Current_RCC_Option == L30MHZ) ? HSI_PLL_MAX : L30MHZ;
    		aula_2_Init(Current_RCC_Option);
    	}
    }
    return 0;
}

