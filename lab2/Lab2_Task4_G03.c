#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_PORT PORTB
#define DEBOUNCE_TIME 700
#define REMAIN_TIME 500

uint8_t binary_number = 0;

ISR(INT0_vect) {
  binary_number = binary_number << 1;
  binary_number &= ~(1 << 0);
  LED_PORT = binary_number;
  _delay_ms(DEBOUNCE_TIME);
        
}

ISR(INT1_vect) {
  binary_number = binary_number << 1;
  binary_number |= (1 << 0);;
  LED_PORT = binary_number; 
  _delay_ms(DEBOUNCE_TIME);
}

void setup() {
    DDRD &= ~((1 << 2) | (1 << 3)); // Configure pin 2 and 3 of PORTD as inputs
    DDRB |= 0x3F; // Configure pins 0,1,2,3,4 and 5 of PORTB as outputs

    EICRA |= (1 << ISC10); // Set the INT1 interrupt request to falling edge
    EICRA |= (1 << ISC11);

    EICRA |= (1 << ISC00); // Set the INTO interrupt request to falling edge
    EICRA |= (1 << ISC01);

    sei(); // Enable global interrupts

    EIMSK |= (1 << INT0); // Enable external interrupt for INTO
    EIMSK |= (1 << INT1); // Enable external interrupt for INT1
}

int main(void) {
    setup();
    while(1) {
        _delay_ms(REMAIN_TIME);
    }
    return 0;
}
