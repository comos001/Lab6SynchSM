/*	Author: victoromosor
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #06  Exercise #02
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include "timer.h"
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_States {START, INC, DEC, RES } state;
unsigned char cnt = 0x00;

void TickFct() {
	switch(state) {
		case START:
			if ((PINA & 0x01) == 0x00)
			{
				cnt = 10;
				state = INC;
			}
			else if ((PINA & 0x02) == 0x00)
			{
				cnt = 10;
				state = DEC;
			}
			else if ((PINA & 0x03) == 0x00)
			{
				state = RES;
			}
			else
			{
				state = START;
			}
			break;
		case INC:
			if ((PINA & 0x01) == 0x00)
			{
				state = INC;
			}
			else
			{
				state = START;
			}
			break;
		case DEC:
			if ((PINA & 0x02) == 0x00)
			{
				state = DEC;
			}
			else
			{
				state = START;
			}
			break;
		case RES:
			state = START;
			break;
		default:
			state = START;
			break;
	}

	switch(state) {
		case START:
			break;
		case INC:
			if (cnt == 10)
			{
				if (PORTB < 9)
				{
					PORTB++;
				}
				cnt = 0;
			}
			else
			{
				cnt++;
			}
			break;
		case DEC:
			if (cnt == 10)
			{
				if (PORTB > 0)
				{
					PORTB--;
				}
				cnt = 0;
			}
			else
			{
				cnt++;
			}
			break;
		case RES:
			PORTB = 0x07;
			break;
		default:
			PORTB = 0x07;
			break;
	}

}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(100);
    TimerOn();
    PORTB = 0x07;
    /* Insert your solution below */
    while (1) {
        while (!TimerFlag);
        TimerFlag = 0;
	TickFct();
    }
    return 1;    

}
