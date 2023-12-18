# include <avr/io.h>
#include <avr/interrupt.h>

int main (void){
    DDRB = DDRB | (1<<5)|(1<<4);
    

    TCNT0 = 0X83; //LOAD TIMER COUNTER REG WITH 0 
    TCNT1 = 0X85EE;

    TCCR0A = 0X00; //SET THE TIMER0  UBDER NORMAL WITH 1:256 PRESCALER
    TCCR0B = 0X04;
    TCCR1A = 0X00; //SET THE TIMER0  UBDER NORMAL WITH 1:256 PRESCALER
    TCCR1B = 0X04;

    TIMSK0 |= (1 << TOIE0); 
    TIMSK1 |= (1 << TOIE1); 
    sei();

    while (1){}
    
}

volatile int over_flow_counter = 0;

ISR(TIMER0_OVF_vect)
{
    over_flow_counter ++;
    if (over_flow_counter > 25){
        PORTB = PORTB ^ (1<<5);
        over_flow_counter = 0;
    }
}

ISR(TIMER1_OVF_vect)
{   
    PORTB = PORTB ^ (1<<4);
    
}
