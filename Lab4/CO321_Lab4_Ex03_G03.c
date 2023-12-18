#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



int main(){
    DDRD |= (1<<PD6);
    uint8_t count = 1;
    TCCR0A = 0b10000011;
    OCR0A = 200;

    while(1){

        // Toggle between prescaler values 8,64,256 and 1024
        switch(count){
            case(1):// 8 prescalar 010
                //7812.5Hz
                TCCR0B = (TCCR0B & ~((1 << CS02) | (1 << CS01) | (1 << CS00))) | (1 << CS01);
                break;
            case(2): //64 prescalar 011
                // 976.56Hz
                TCCR0B = (TCCR0B & ~((1 << CS02) | (1 << CS01) | (1 << CS00))) | (1 << CS01) |(1<<CS00);
                break;
            case(3): //256 prescalar 100
                // 244.14Hz
                TCCR0B = (TCCR0B & ~((1 << CS02) | (1 << CS01) | (1 << CS00))) | (1 << CS02);
                break;
            case(4): //1024 prescalar 101
                //61.04Hz
                TCCR0B = (TCCR0B & ~((1 << CS02) | (1 << CS01) | (1 << CS00))) | (1 << CS02) | (1 << CS00);
                break;
        }

        _delay_ms(1000);
        count++;

        if (count > 4) {
            count = 1;
        }

    }
}
