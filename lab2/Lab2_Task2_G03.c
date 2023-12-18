#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BUTTON_PIN INT0
#define LED_PIN PB0

ISR(INT0_vect) {
    // Toggle LED_PIN
    PORTB ^= (1 << LED_PIN);
    _delay_ms(1000);
}

void setup() {
    DDRB |= 0x3F; /// Configure pins 0,1,2,3,4 and 5 of PORTB as outputs
    DDRD &= ~(1 << BUTTON_PIN); // Configure BUTTON_PIN as input

    EICRA |= (1 << ISC01); // Set the interrupt request to falling edge
    EICRA &= ~(1 << ISC00);

    sei(); // Enable global interrupts

    EIMSK |= (1 << INT0); // Enable external interrupt for BUTTON_PIN
}

int main(void) {
    setup();
    while(1) {

        // Main loop can be empty, the work is done in the ISR
    }
    return 0;
}