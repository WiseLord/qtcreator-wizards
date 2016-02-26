#include <stm32f10x.h>

GPIO_InitTypeDef led1, led3;

void SysTick_Handler(void) {
	static uint16_t tick = 0;

	if (++tick >= 20)
		tick = 0;

	switch (tick) {
	case 0:
		GPIO_ResetBits(GPIOA, led1.GPIO_Pin);
		GPIO_SetBits(GPIOA, led3.GPIO_Pin);
		break;
	case 10:
		GPIO_ResetBits(GPIOA, led3.GPIO_Pin);
		GPIO_SetBits(GPIOA, led1.GPIO_Pin);
		break;
	}
}

void hwInit()
{
	// Enable port A
	RCC->APB2ENR |= RCC_APB2Periph_GPIOA;

	// Init leds
	led1.GPIO_Pin = GPIO_Pin_2;
	led1.GPIO_Mode = GPIO_Mode_Out_PP;
	led1.GPIO_Speed = GPIO_Speed_2MHz;

	led3.GPIO_Pin = GPIO_Pin_3;
	led3.GPIO_Mode = GPIO_Mode_Out_PP;
	led3.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOA, &led1);
	GPIO_Init(GPIOA, &led3);

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


