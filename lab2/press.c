#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BLINK_DELAY_MS 1000

int main(void)
{
    DDRD &= ~(1<<7);
    DDRB = 0b00111111;
    unsigned char count;

    EICRA |= (1<<ISC01);
    EICRA |= (1<<ISC00);

    sei();

    EIMSK |= (1<<INT0);

    while (1)
    {
        PORTB = count
    }
    return 0;
}

ISR(INT0_vect)
{
    count++;
}