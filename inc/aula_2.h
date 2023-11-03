


typedef enum {
	HSI_Default = 0,
	HSI_PLL_MAX ,
	HSE_Default ,
	HSE_PLL_MAX ,
	L30MHZ,
	NotConfiguration,
}RCC_ConfigOptions;

void aula_2_Init(RCC_ConfigOptions RCC_ConfigOption);

