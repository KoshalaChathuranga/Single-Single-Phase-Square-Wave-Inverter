#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t Duty_Cycle = 0;

int main(void)
{
	DDRD |= (1 << PORTD6);
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TCCR0B = (1 << CS00);
	TIMSK0 |= (1 << TOIE0);
	sei();
	
	while (1)
	{
		_delay_ms(100);
		Duty_Cycle += 50;
		if (Duty_Cycle > 50)
		{
			Duty_Cycle = 50;
		}
	}
}

ISR(TIMER0_OVF_vect)
{
	OCR0A = (Duty_Cycle * 255) / 100;
}
