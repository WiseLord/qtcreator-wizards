 #include <stm32f10x.h>

GPIO_InitTypeDef ledG, ledB;

void SysTick_Handler(void) {
  static uint16_t tick = 0;

  if (++tick >= 20)
    tick = 0;

  switch (tick) {
    case 0:
      GPIO_ResetBits(GPIOC, ledB.GPIO_Pin);
      GPIO_SetBits(GPIOC, ledG.GPIO_Pin);
    break;
    case 10:
      GPIO_ResetBits(GPIOC, ledG.GPIO_Pin);
      GPIO_SetBits(GPIOC, ledB.GPIO_Pin);
    break;
  }
}

void hwInit()
{
  // Enable port C
  RCC->APB2ENR |= RCC_APB2Periph_GPIOC;

  // Init leds
  ledB.GPIO_Pin = GPIO_Pin_8;
  ledB.GPIO_Mode = GPIO_Mode_Out_PP;
  ledB.GPIO_Speed = GPIO_Speed_2MHz;

  ledG.GPIO_Pin = GPIO_Pin_9;
  ledG.GPIO_Mode = GPIO_Mode_Out_PP;
  ledG.GPIO_Speed = GPIO_Speed_2MHz;

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

