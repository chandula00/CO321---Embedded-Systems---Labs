#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PD7
#define LED_PORT PORTB

int main(void) {
    DDRD &= ~(1 << BUTTON_PIN); // Configure BUTTON_PIN as input
    DDRB |= 0x3F; // Configure pins 0,1,2,3,4 and 5 of PORTB as outputs

    uint8_t count = 0;
    uint8_t last_button_state = 0;

    while (1) { 
        uint8_t button_state = PIND & (1 << BUTTON_PIN);
        if (button_state != last_button_state) {
            _delay_ms(200); // Debounce delay
            if (button_state != last_button_state) {
                if (button_state != 0) {
                    count++;
                    LED_PORT = count;
                }
                last_button_state = button_state;
            }
        }
    }

    return 0;
}
