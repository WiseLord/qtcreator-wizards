#include <avr/io.h>
#include <util/delay.h>

#include "pins.h"

int main(void)
{
    OUT(LED);

    while (1) {
        CLR(LED);
        _delay_ms(250);
        SET(LED);
        _delay_ms(250);
    }

    return 0;
}
