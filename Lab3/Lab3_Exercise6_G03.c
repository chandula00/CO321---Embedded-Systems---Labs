#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow_count0 = 0;
volatile uint8_t overflow_count1 = 0;

ISR(TIMER0_OVF_vect)
{
    overflow_count0++;
    if (overflow_count0 >= 25) // 50ms / 2ms = 25
    {
        PORTB ^= (1 << 5); // toggle LED1
        overflow_count0 = 0;
    }
}

ISR(TIMER1_OVF_vect)
{
    
    PORTB ^= (1 << 4); // toggle LED2
        
}

int main(void)
{
    DDRB |= (1 << 5);  // set PB5 as output
    DDRB |= (1 << 4);  // set PB6 as output
    PORTB |= (1 << 5); // initially turn LED1 on
    PORTB |= (1 << 4); // initially turn LED2 on

    TCNT0 = 131;  // initialize counter
    TCCR0A = 0X00; // normal mode
    TCCR0B = 0X04; // set prescaler to 256

    TCNT1 = 34286;  // initialize counter
    TCCR1A = 0X00; // normal mode
    TCCR1B = 0X04; // set prescaler to 256

    TIMSK0 |= (1 << TOIE0); // enable timer0 overflow interrupt
    TIMSK1 |= (1 << TOIE1); // enable timer1 overflow interrupt
    sei();                  // enable global interrupts

    while (1)
    {
    }

    return 0;
}
