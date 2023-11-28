#include "stm32f10x_tim.h"
static MotorControlGPIO_INIT(void)
{
	//Enable GPIO Clock
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure_PWM_Output_1;
	GPIO_InitTypeDef GPIO_InitStructure_PWM_Output_2;
	//GPIO cfg - Motor 1
	GPIO_InitStructure_PWM_Output_1.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure_PWM_Output_1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_PWM_Output_1.GPIO_Mode = GPIO_Mode_AF_PP;
	//GPIO cfg - Motor 2
	GPIO_InitStructure_PWM_Output_2.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure_PWM_Output_2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure_PWM_Output_2.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(GPIOA, &GPIO_InitStructure_PWM_Output_1);
	GPIO_Init(GPIOA, &GPIO_InitStructure_PWM_Output_2);
}


static PWM_Timers_init(void)
{
	//Enable TIM2/4 Clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//info: sistr3 page 14
	//TIM struct CFG variable
	//T=((PSC+1)/CK_INT)*(ARR+1)
	//CK_INT = TIM3 Clock Freq. = 36MHz because it belongs to APB1
	//neads to handle values between 150 µs(min) to 38 ms(sensor time out)
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	//TIM 2 CFG
	TIM_TimeBaseStructure.TIM_Period = 38999; //38999dec
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_Prescaler = 71; //35dec
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	//TIM Init
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

return;
}


static PWM_Output_init(void)
{
	/* Configura o Canal1 do TIM2 em Toggle Mode */
	TIM_OCInitTypeDef TIM_OCInitStructure;

	//TIM 2 CFG
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0x1FFF; //PWM25%
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	//TIM2 Init
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);

return;
}
void MotorControl_Init(void)
{
	//GPIO CFG
	MotorControlGPIO_INIT();
	//Timers initialization
	PWM_Timers_init();
	//PWM output initialization
	PWM_Output_init();

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
