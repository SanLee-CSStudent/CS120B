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

enum STATE{Start, Init, Inc, Dec, IncR, DecR, Reset} state;

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
			// unsigned char tempA = (PINA & 0x01);
			state = IncR;
			
			break;
		case IncR:
			if(PINA == 0x01){
				state = IncR;
			}
			else {
				state = Init;
			}
			break;
		case Dec:
			// unsigned char tempB = (PINA & 0x02);
			if(PINA == 0x02){
				state = DecR;
			}
			else{
				state = Init;
			}
			break;
		case DecR:
			if(PINA == 0x02){
				state = DecR;
			}
			else {
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
			PORTC = 0x00;
		break;
		case Init:

		break;
		case Inc:
			if(PORTC < 0x09){
				PORTC++;
			}
		break;
		case Dec:
			if(PORTC > 0){
				PORTC = PORTC - 1;
			}
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
