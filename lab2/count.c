#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BLINK_DELAY_MS 1500

int main(void)
{
    DDRD = 0b10000000;
    DDRB = 0b00111111;
    unsigned char count = 0;

    while (count < 64)
    {
        if (PIND & (1<<7)){
            count ++;
        } 
        PORTB = count;
        _delay_ms(BLINK_DELAY_MS);
        
    }
    return 0;
}
