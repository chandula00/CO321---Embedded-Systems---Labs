#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow_count = 0;

ISR(TIMER0_OVF_vect)
{
    overflow_count++;
    if (overflow_count >= 25)
    {                      // 100ms / 4ms = 25
        PORTB ^= (1 << 5); // toggle LED
        overflow_count = 0;
    }
}

int main(void)
{
    DDRB |= (1 << 5);  // set PB5 as output
    PORTB |= (1 << 5); // initially turn LED on

    TCNT0 = 0X06;  // initialize counter
    TCCR0A = 0X00; // normal mode
    TCCR0B = 0X04; // set prescaler to 256

    TIMSK0 |= (1 << TOIE0); // enable timer overflow interrupt
    sei();                  // enable global interrupts

    while (1)
    {
    }

    return 0;
}
