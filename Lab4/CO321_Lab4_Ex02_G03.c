#include <avr/io.h>
#include <util/delay.h>


#define LED_PIN PD6

int main(void)
{
    DDRD |= (1 << LED_PIN);  // Set LED_PIN as output

    // Set Fast PWM mode, non-inverting output
    TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
    TCCR0B |= (1 << CS01) | (1 << CS00);  // Set prescaler to 64

    while (1)
    {
        // Fade in
        for (uint8_t i = 0; i < 255; i++)
        {
            OCR0A = i;
            _delay_ms(10);
        }

        // Fade out
        for (uint8_t i = 255; i > 0; i--)
        {
            OCR0A = i;
            if (i>5){
                _delay_ms(10);
            }
        }
    }

    return 0;
}
