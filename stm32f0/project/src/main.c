#include <stm32f0xx.h>
#include <stm32f0xx_gpio.h>

// #include "pins.h"

GPIO_InitTypeDef ledG, ledB;

void SysTick_Handler(void) {
	static uint16_t tick = 0;

	if (++tick >= 20)
		tick = 0;

	switch (tick) {
	case 0:
		GPIO_ResetBits(GPIOC, ledB.GPIO_Pin);
		// GPIO_CLR(LED_B);
		GPIO_SetBits(GPIOC, ledG.GPIO_Pin);
		// GPIO_SET(LED_G);
		break;
	case 10:
		// GPIO_CLR(LED_C);
		GPIO_ResetBits(GPIOC, ledG.GPIO_Pin);
		GPIO_SetBits(GPIOC, ledB.GPIO_Pin);
		// GPIO_SET(LED_B);
		break;
	}
}

void hwInit()
{
	// Enable port C
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	// Init leds
	ledB.GPIO_Pin = GPIO_Pin_8;
	ledB.GPIO_Mode = GPIO_Mode_OUT;
	ledB.GPIO_Speed = GPIO_Speed_2MHz;
	ledB.GPIO_OType = GPIO_OType_PP;
	ledB.GPIO_PuPd = GPIO_PuPd_NOPULL;
	// GPIO_OUT(LED_B);

	ledG.GPIO_Pin = GPIO_Pin_9;
	ledG.GPIO_Mode = GPIO_Mode_OUT;
	ledG.GPIO_Speed = GPIO_Speed_2MHz;
	ledG.GPIO_OType = GPIO_OType_PP;
	ledG.GPIO_PuPd = GPIO_PuPd_NOPULL;
	// GPIO_OUT(LED_G);

	GPIO_Init(GPIOC, &ledB);
	GPIO_Init(GPIOC, &ledG);

	return;
}

int main(void)
{
	hwInit();

	SysTick_Config(SystemCoreClock/10);

	while(1) {
		;
	}

	return 0;
}
