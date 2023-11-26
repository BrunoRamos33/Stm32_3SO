#include "stm32f10x_tim.h"

void MotorControl_Init(void)
{
	//Falta configurar os GPIOS
	//TIM2 CH1 é o PA0 mas já está ocupado, ver outro
	//começar por marcar todos os GPOIOS em uso
	//Enable TIM2 and TIM4 Clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/* Configura o Canal1 do TIM2 em Toggle Mode */
	TIM_OCInitTypeDef TIM_OCInitStructure;

	//TIM 2 CFG
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0x3FFF; //PWM25%
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	//TIM2 Init
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);

return;
}

void MotorControl_Enable(void)
{
	//Enable TIM2
	TIM_Cmd(TIM2, ENABLE);

	return;
}

void MotorControl_Disable(void)
{
	//Enable TIM2
	TIM_Cmd(TIM2, DISABLE);

	return;
}

void MotorControl_SetCompare(uint16_t f_compare_reg_value)
{
	//Enable TIM2
	TIM_SetCompare2(TIM2, f_compare_reg_value);

	return;
}
