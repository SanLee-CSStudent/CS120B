/*	Author: slee488
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATE{Start, Init, Inc, Dec, Simul, Reset} state;
char c = PORTC;
void Tick(){
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if(PINA == 0x01){
				state = Inc;
			}
			else if(PINA == 0x02){
				state = Dec;
			}
			else if(PINA == 0x03){
				state = Reset;
			}
			else {
				state = Init;
			}

			break;
		case Inc:
			if(PINA == 0x00){
				state = Init;
			}
			else{
				state = Simul;
			}
			break;
		case Dec:
			if(PINA == 0x00){
				state = Init;
			}
			else{
				state = Simul;
			}
			break;
		case Simul:
			if(PINA == 0x00){
				state = Reset;
			}
			else if(PINA == 0x03){
				state = Simul;
			}
			else{
				state = Init;
			}
			break;
		case Reset:
			state = Init;
			break;
		default:
			break;
	}
	
	switch(state){
		case Start:
			PORTC = 0x07;
		break;
		case Init:
			PORTC = 0x07;
		break;
		case Inc:
			if(c < 0x09){
				PORTC = PORTC + 1;
			}
		break;
		case Dec:
			if(c > 0){
				PORTC = PORTC - 1;
			}
		break;
		case Simul:
			
		break;
		case Reset:
			PORTC = 0x00;
		break;
		default:
		break;
	}
}

int main(void) {
	DDRA = 0x00;PORTA = 0xFF;
	DDRC = 0xFF;PORTC = 0x00;
    /* Insert DDR and PORT initializations */
	state = Start;
    /* Insert your solution below */
    while (1) {
		Tick();
    }
    return 1;
}
