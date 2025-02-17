/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//DEMO: https://drive.google.com/open?id=1dramam

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, INIT, INCREASE, DECREASE, WAIT_IN, WAIT_DE, RESET} state;
unsigned char button0;
unsigned char button1;

void Tick()
{
	button0 = (~PINA & 0x01);
	button1 = (~PINA & 0x02);

	switch(state) {
		case START:
			state = INIT;
			break;

		case INIT:

			if(button0 && !button1)
			{
				state = INCREASE;
			}
			else if(!button0 && button1)
			{
				state = DECREASE;
			}
			else if(button0 && button1)
			{
				state = RESET;
			}
			else
			{
				state = INIT;
			}

			break;

		case INCREASE:

			state = WAIT_IN;
			break;

		case DECREASE:

			state = WAIT_DE;
			break;

		case WAIT_IN:

			if(!button0 && !button1)
			{
				state = INIT;
			}
			else if(button0 && button1)
			{
				state = RESET;
			}
			else
			{
				state = WAIT_IN;
			}

			break;

		case WAIT_DE:

			if(!button0 && !button1)
			{
				state = INIT;
			}
			else if(button0 && button1)
			{
				state = RESET;
			}
			else
			{
				state = WAIT_DE;
			}

			break;

		case RESET:

			state = WAIT_DE;
			break;

		default:

			state = START;
			break;
	}

	switch(state)
	{
		case START:
			break;

		case INIT:
			break;

		case INCREASE:
			if(PORTC < 9)
			{
				PORTC = PORTC + 1;
			}
			else
			{
				PORTC = 0x09;
			}

			break;

		case DECREASE:
			if(PORTC > 0)
			{
				PORTC = PORTC -1;
			}
			else
			{
				PORTC = 0x00;
			}

			break;

		case RESET:
			PORTC = 0x00;
			break;
	}

}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	state = START;
	PORTC = 0x00;

	while(1) {
		Tick();
	}

		return 0;
}
