#include "aula_2.h"
#include "stm32f10x_rcc.h"

RCC_ConfigOptions currentRCC_cfg_op = NotConfiguration;

//HCLK with Oscilador interno HSI, no seu valor por omissão (8 M Hz).
//PCLK1 MAx 36MHz
//PCLK2 MAx 72MHz
static void RCC_Config_HSI_Default(void)
{
	//1-Enable HSI OScilator
	RCC_HSICmd(ENABLE);

	//2-Check if Clk signal is ready
	while( RCC_GetFlagStatus( RCC_FLAG_HSIRDY ) == RESET );

	//3-Flash config
	//- 0 wait states se 0 < SYSCLK ≤ 24 MHz;
	//– 1 wait states se 24 MHz < SYSCLK ≤ 48 MHz;
	//– 2 wait states se 48 MHz < SYSCLK ≤ 72 MHz.
	FLASH_SetLatency(FLASH_Latency_0);

	//4-AHB prescaler cfg
	RCC_HCLKConfig(RCC_SYSCLK_Div1);

	//5-APB1 prescaler cfg - not in use
	RCC_PCLK1Config(RCC_HCLK_Div1);

	//5-APB2 prescaler cfg
	RCC_PCLK2Config(RCC_HCLK_Div1);
	//6,7,8 PLL cfg - Not in use

	//9-Configure Clk source
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

	//10-Clk source is correct?
	//if ClkSource == HSI then return 0x00
	//if ClkSource == HSE then return 0x04
	//if ClkSource == PLL then return 0x08
	while(RCC_GetSYSCLKSource() != 0x00);
	return;
}
static void RCC_Config_HSI_PLL_Max(void)
{
	//1-Enable HSI OScilator
	RCC_HSICmd(ENABLE);
	//2-Check if Clk signal is ready
	while( RCC_GetFlagStatus( RCC_FLAG_HSIRDY ) == RESET );
	//3-Flash config
	//- 0 wait states se 0 < SYSCLK ≤ 24 MHz;
	//– 1 wait states se 24 MHz < SYSCLK ≤ 48 MHz;
	//– 2 wait states se 48 MHz < SYSCLK ≤ 72 MHz.
	FLASH_SetLatency(FLASH_Latency_2);

	//4-AHB prescaler cfg
	RCC_HCLKConfig(RCC_SYSCLK_Div1);

	//5-APB1 prescaler cfg - not in use
	RCC_PCLK1Config(RCC_HCLK_Div2);

	//5-APB2 prescaler cfg
	RCC_PCLK2Config(RCC_HCLK_Div1);

	//6-Configure PLL
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_16);

	//7-Enable PLL
	RCC_PLLCmd(ENABLE);

	//8-Check if Clk signal is ready
	while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY ) == RESET );

	//9-Configure Clk source
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	//10-Clk source is correct?
	//if ClkSource == HSI then return 0x00
	//if ClkSource == HSE then return 0x04
	//if ClkSource == PLL then return 0x08
	while(RCC_GetSYSCLKSource() != 0x08);
	return;
}
//External Osc is 12MHz
static void RCC_Config_HSE_Default(void)
{
	ErrorStatus HSEStartUpStatus;

	//1-Enable HSE OScilator
	RCC_HSEConfig(RCC_HSE_ON);
	//2-Check if Clk signal is ready
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS)
	{
		/*fazer as outras configurações necessárias, p.e.: configurar flash , SYSCLK,
		PLL, etc.*/
		//3-Flash config
		//- 0 wait states se 0 < SYSCLK ≤ 24 MHz;
		//– 1 wait states se 24 MHz < SYSCLK ≤ 48 MHz;
		//– 2 wait states se 48 MHz < SYSCLK ≤ 72 MHz.
		FLASH_SetLatency(FLASH_Latency_0);

		//4-AHB prescaler cfg
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		//5-APB1 prescaler cfg - not in use
		RCC_PCLK1Config(RCC_HCLK_Div1);

		//5-APB2 prescaler cfg
		RCC_PCLK2Config(RCC_HCLK_Div1);
		//6,7,8 PLL cfg - Not in use

	}
	else
	{
		//Error
		while(1);
	}
	//Configure Clk source
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
	//if ClkSource == HSI then return 0x00
	//if ClkSource == HSE then return 0x04
	//if ClkSource == PLL then return 0x08
	while(RCC_GetSYSCLKSource() != 0x04);
	return;
}
static void RCC_Config_HSE_PLL_Max(void)
{
	ErrorStatus HSEStartUpStatus;

	//1-Enable HSE OScilator
	RCC_HSEConfig(RCC_HSE_ON);
	//2-Check if Clk signal is ready
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS)
	{
		/*fazer as outras configurações necessárias, p.e.: configurar flash , SYSCLK,
		PLL, etc.*/
		//3-Flash config
		//- 0 wait states se 0 < SYSCLK ≤ 24 MHz;
		//– 1 wait states se 24 MHz < SYSCLK ≤ 48 MHz;
		//– 2 wait states se 48 MHz < SYSCLK ≤ 72 MHz.
		FLASH_SetLatency(FLASH_Latency_2);

		//4-AHB prescaler cfg
		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		//5-APB1 prescaler cfg
		RCC_PCLK1Config(RCC_HCLK_Div2);

		//5-APB2 prescaler cfg
		RCC_PCLK2Config(RCC_HCLK_Div1);

		//6-Configure PLL
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);

		//7-Enable PLL
		RCC_PLLCmd(ENABLE);

		//8-Check if Clk signal is ready
		while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY ) == RESET );

	}
	else
	{
		//Error
		while(1);
	}

	//Configure Clk source
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	//if ClkSource == HSI then return 0x00
	//if ClkSource == HSE then return 0x04
	//if ClkSource == PLL then return 0x08
	while(RCC_GetSYSCLKSource() != 0x08);
	return;
}
static void RCC_Config_30MHz(void)
{
	ErrorStatus HSEStartUpStatus;

	//1-Enable HSE OScilator
	RCC_HSEConfig(RCC_HSE_ON);
	//2-Check if Clk signal is ready
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS)
	{
		/*fazer as outras configurações necessárias, p.e.: configurar flash , SYSCLK,
		PLL, etc.*/
		//3-Flash config
		//- 0 wait states se 0 < SYSCLK ≤ 24 MHz;
		//– 1 wait states se 24 MHz < SYSCLK ≤ 48 MHz;
		//– 2 wait states se 48 MHz < SYSCLK ≤ 72 MHz.
		FLASH_SetLatency(FLASH_Latency_2);

		//4-AHB prescaler cfg
		RCC_HCLKConfig(RCC_SYSCLK_Div2);

		//5-APB1 prescaler cfg - not in use
		RCC_PCLK1Config(RCC_HCLK_Div2);

		//5-APB2 prescaler cfg
		RCC_PCLK2Config(RCC_HCLK_Div1);

		//6-Configure PLL
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_5);

		//7-Enable PLL
		RCC_PLLCmd(ENABLE);

		//8-Check if Clk signal is ready
		while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY ) == RESET );

	}
	else
	{
		//Error
		while(1);
	}

	//Configure Clk source
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	//if ClkSource == HSI then return 0x00
	//if ClkSource == HSE then return 0x04
	//if ClkSource == PLL then return 0x08
	while(RCC_GetSYSCLKSource() != 0x08);
	return;
}

void aula_2_Init(RCC_ConfigOptions RCC_ConfigOption)
{
	switch(RCC_ConfigOption)
	{
		case HSI_Default:
		{
			RCC_Config_HSI_Default();
			break;
		}
		case HSI_PLL_MAX:
		{
			RCC_Config_HSI_PLL_Max();
			break;
		}
		case HSE_Default:
		{
			RCC_Config_HSE_Default();
			break;
		}
		case HSE_PLL_MAX:
		{	//Core at 72MHz
			RCC_Config_HSE_PLL_Max();
			break;
		}
		case L30MHZ:
		{
			RCC_Config_30MHz();
			break;
		}
		default :
			break;
	}
	return;
}



