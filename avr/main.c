#include <avr/io.h>
#include <util/delay.h>

#include "pins.h"

int main(void)
{
    OUT(LED_RED);

    while (1) {
        CLR(LED_RED);
        _delay_ms(250);
        SET(LED_RED);
        _delay_ms(250);
    }

    return 0;
}
