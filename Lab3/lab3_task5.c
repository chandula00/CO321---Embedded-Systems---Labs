#include <avr/io.h>

void delay_timer0()
{
    TCNT0 = 0X06; // LOAD TIMER COUNTER REG WITH 0

    TCCR0A = 0X00; // SET THE TIMER0  UBDER NORMAL WITH 1:256 PRESCALER
    TCCR0B = 0X04;

    while ((TIFR0 & 0X01) == 0)
        ; // WAIT TILL TIMER OVERFLOW BIT (T0V0) IS SET

    TCCR0B = 0X00; // CLEAR TIMER SETTINGS(THIS STOPS THE TIMER)
    TCCR0A = 0X00;

    TIFR0 = 0X01;
}

int main(void)
{
    DDRB = DDRB | (1 << 5);
    PORTB = PORTB | (1 << 5); // initially led ON

    while (1)
    {
        for (int x = 0; x < 25; x++)
        {
            delay_timer0();
        }
        PORTB = PORTB ^ (1 << 5); // toggle led
    }
}