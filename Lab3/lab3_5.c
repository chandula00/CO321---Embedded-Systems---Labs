# include <avr/io.h>
#include <avr/interrupt.h>

int main (void){
    DDRB = DDRB | (1<<5);
    PORTB = PORTB | (1<<5); //initially led ON

    TCNT0 = 0X06; //LOAD TIMER COUNTER REG WITH 0 

    TCCR0A = 0X00; //SET THE TIMER0  UBDER NORMAL WITH 1:256 PRESCALER
    TCCR0B = 0X04;

    TIMSK |= (1 << TOIE1); 
    sei();

    while (1){}
    
}

volatile int over_flow_counter = 0;

ISR(TIMER1_OVF_vect)
{
    over_flow_counter ++;
    if (over_flow_counter > 25){
        PORTB = PORTB ^ (1<<5);
        over_flow_counter = 0;
    }
}

