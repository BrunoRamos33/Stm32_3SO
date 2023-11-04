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
#include "aula_1.h"
#include "aula_2.h"
#include "USART.h"
#include "PC_Comm.h"

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
	char string[64];
	char stringDebug[64];
	char tempchar;
	unsigned char count = 0;
	RCC_ConfigOptions Current_RCC_Option = HSE_PLL_MAX;
	//RCC Init
	aula_2_Init(Current_RCC_Option);

	//GPIO Initializations - LED
	aula_1_Init();

	//GPIO Initializations - USART
	USART_2_GPIO_Init();

	//USART INIT
	USART_2_Init();

	//say hello
	USART_2_sendString("\rPC_Comm.c ready to communicate.\r");
  
	// identify yourself specifically
	USART_2_sendString("\rYou are talking to the PC_Comm demo.\r");

    /* Infinite loop */
    for(;;)
    {
    	//Blincking LED
//    	aula_1_Action();

		// Check to see if a character is waiting
		if( USART_2_isCharAvailable() == 1 )
		{

			//If a new character is received, get it
			string[count++] = USART_2_receiveChar();

			//receive a packet up to 64 bytes long
			if((uint8_t)string[count-1] == (uint8_t)0x0A)// HyperTerminal string ends with \r\n
			{
				string[count-2] = '\0'; //convert to a string
				PC_Comm_parseInput(string);
				string[0] = '\0';
				count = 0;
			}
			else if(count > 64)
			{
				count = 0;
				string[0] = '\0';
				USART_2_sendString("Error - received > 64 characters");
			}
		}
    }
    return 0;
}

