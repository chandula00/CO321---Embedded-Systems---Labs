#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BUTTON_A_PIN INT0
#define BUTTON_B_PIN INT1
#define LED_PORT PORTB

volatile uint8_t binary_number = 0;

void print_binary(int num) {
    if (num == 0) {
        return;
    }
    print_binary(num / 2);
    printf("%d", num % 2);
}

ISR(BUTTON_A_PIN_vect) {
    binary_number <<= 1;
    // print binary_number
    print_binary(binary_number);
    LED_PORT = binary_number;
}

ISR(BUTTON_B_PIN_vect) {
    binary_number = (binary_number << 1) | 1;
    // print binary_number
    LED_PORT = binary_number;
}

void setup() {
    DDRD &= ~((1 << 2) | (1 << 3)); // Configure pin 2 and 3 of PORTD as inputs
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
