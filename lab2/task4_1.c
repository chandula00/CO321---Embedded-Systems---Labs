#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUTTON_A_PIN INT0
#define BUTTON_B_PIN INT1
#define LED_PORT PORTB
#define DEBOUNCE_TIME 20
#define REMAIN_TIME 500

volatile uint8_t binary_number = 0;

ISR(BUTTON_A_PIN_vect) {
    _delay_ms(DEBOUNCE_TIME);
    binary_number <<= 1;
    LED_PORT = binary_number;
  	LED_PORT &= ~(1 << 0);
        
}

ISR(BUTTON_B_PIN_vect) {
    _delay_ms(DEBOUNCE_TIME);
    binary_number = binary_number << 1;
    LED_PORT = binary_number;
  	LED_PORT |= (1 << 0); 
    
}

void setup() {
    DDRD &= ~((1 << 6) | (1 << 7)); // Configure pin 2 and 3 of PORTD as inputs
    DDRB |= 0x3F; // Configure pins 0,1,2,3,4 and 5 of PORTB as outputs

    EICRA |= (1 << ISC10); // Set the INT1 interrupt request to falling edge
    EICRA &= ~(1 << ISC11);

    EICRA |= (1 << ISC00); // Set the INTO interrupt request to falling edge
    EICRA &= ~(1 << ISC01);

    sei(); // Enable global interrupts

    EIMSK |= (1 << INT0); // Enable external interrupt for INTO
    EIMSK |= (1 << INT1); // Enable external interrupt for INT1
}

int main(void) {
    setup();
    while(1) {
        // Main loop can be empty, the work is done in the ISR
    }
    return 0;
}