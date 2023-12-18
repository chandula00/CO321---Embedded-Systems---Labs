#include <avr/io.h>

void setupPWM() {
    // Set the Fast PWM mode and non-inverting output
    TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);

    // Set the prescaler to 64 and starts PWM
    TCCR0B = (1 << CS01)|(1 << CS01) | (0 << WGM02);

    // Set the duty cycle to 50%
    OCR0A = 127;
}

int main(void) {
    // Set the PORTD as Output
    DDRD = (1 << PORTD6);

    setupPWM();

    while (1) {
        // Do nothing... PWM is handled by timer
    }

    return 0;
}

