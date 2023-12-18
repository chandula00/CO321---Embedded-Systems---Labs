#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100
int main(void)
{
    DDRB = 0b0111111;   /* configure pin i of PORTB for output*/
    while (1)
    {
        for (int i = 5; i > 0; i--)
        {
            PORTB = PORTB | (1 << i); /* set pin i high to turn led on */
            _delay_ms(BLINK_DELAY_MS);
            PORTB = PORTB & ~(1 << i); /* set pin i low to turn led off */
        }

        for (int i = 0; i < 5; i++)
        {
            PORTB = PORTB | (1 << i); /* set pin i high to turn led on */
            _delay_ms(BLINK_DELAY_MS);
            PORTB = PORTB & ~(1 << i); /* set pin i low to turn led off */
        }
    }
}