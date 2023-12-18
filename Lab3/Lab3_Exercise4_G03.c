#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define BLINK_DELAY_MS 100


int main(void)
{
    DDRB |= 0b00011111; /* configure pin 1,2,3,4,5 of PORTB for output*/

    TCNT1 = 0XBDC; // LOAD TIMER COUNTER REG WITH

    TCCR1A = 0X00; // SET THE TIMER0  UBDER NORMAL WITH 1:256 PRESCALER
    TCCR1B = 0X04;

    TIMSK1 |= (1 << TOIE1);
    sei();

    while (1)
    {
        for (int i = 4; i > 0; i--)
        {
            PORTB = PORTB | (1 << i); /* set pin i high to turn led on */
            _delay_ms(BLINK_DELAY_MS);
            PORTB = PORTB & ~(1 << i); /* set pin i low to turn led off */
        }
        for (int i = 2; i < 4; i++)
        {
            PORTB = PORTB | (1 << i); /* set pin i high to turn led on */
            _delay_ms(BLINK_DELAY_MS);
            PORTB = PORTB & ~(1 << i); /* set pin i low to turn led off */
        }
    }
}

ISR(TIMER1_OVF_vect)
{
    PORTB = PORTB ^(1 << 5); //toggle PB5

}