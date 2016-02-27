#include <stm32f10x.h>

GPIO_InitTypeDef led;

void SysTick_Handler(void) {
	static uint16_t tick = 0;

	if (++tick >= 20)
		tick = 0;

	switch (tick) {
	case 0:
		GPIO_ResetBits(GPIOC, led.GPIO_Pin);
		break;
	case 10:
		GPIO_SetBits(GPIOC, led.GPIO_Pin);
		break;
	}
}

void hwInit()
{
	// Enable port A
	RCC->APB2ENR |= RCC_APB2Periph_GPIOC;

	// Init led
	led.GPIO_Pin = GPIO_Pin_13;
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	led.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOC, &led);

	return;
}

int main(void)
{
	hwInit();

	SysTick_Config(SystemCoreClock/10);

	while(1) {
	}

	return 0;
}


