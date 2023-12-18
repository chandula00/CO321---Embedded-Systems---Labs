#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 700

int main()
{

    DDRD &= ~((1 << 2) | (1 << 3)); /* configure pin 2 and 3 of PORTD as inputs*/
    DDRB |= 0x3F;                   /* configure pins 0,1,2,3,4 and 5 of PORTB as outputs*/

    EICRA |= (1 << ISC00); /* Set the INTO interrupt request to rising edge */
    EICRA |= (1 << ISC01); /* Set the INTO interrupt request to rising edge */

    EICRA |= (1 << ISC10); /* Set the INT1 interrupt request to rising edge */
    EICRA |= (1 << ISC11); /* Set the INT1 interrupt request to rising edge */

    sei(); /* Enable global interrupts */

    EIMSK |= (1 << INT0); /* Enable external interrupt for INTO */
    EIMSK |= (1 << INT1); /* Enable external interrupt for INT1 */

    while (1)
    {
    }
    return 0;
}

ISR(INT0_vect)
{
    _delay_ms(BLINK_DELAY_MS); /* Assign the delay */
    PORTB = PORTB << 1; // Left shift the PORTB value
    PORTB &= ~(1 << 0); // Clear the 0th bit of PORTB
}

ISR(INT1_vect)
{
    _delay_ms(BLINK_DELAY_MS); /* Assign the delay */
    PORTB = PORTB << 1; // Left shift the PORTB value
    PORTB |= (1 << 0);  // Set the 0th bit of PORTB
}