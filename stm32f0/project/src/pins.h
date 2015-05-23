#ifndef PINS_H
#define PINS_H

#define CONCAT(x,y)			x ## y

#define GPIO_SET(x)			(CONCAT(x, _PORT)->BSRR = 1 << CONCAT(x, _LINE))
#define GPIO_CLR(x)			(CONCAT(x, _PORT)->BRR = 1 << CONCAT(x, _LINE))
#define GPIO_IN(x)			(CONCAT(x, _PORT)->MODER |= 0b00 << 2 * CONCAT(x, _LINE))
#define GPIO_OUT(x)			(CONCAT(x, _PORT)->MODER |= 0b01 << 2 * CONCAT(x, _LINE))

#define LED_G_PORT			GPIOC
#define LED_G_LINE			9
#define LED_B_PORT			GPIOC
#define LED_B_LINE			8

#endif // PINS_H
