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

enum STATE{Start, LZeroPress, LZeroRelease, LOnePress, LOneRelease} state;

void Tick(){
	switch(state){
		case Start:
			state = LZeroRelease;
			break;
		case LZeroPress:
			if(PINA == 0x01){
				state = LZeroPress;
			}
			else{
				state = LZeroRelease;
			}
			break;
		case LZeroRelease:
			if(PINA == 0x00){
				state = LOnePress;
			}
			else{
				state = LZeroRelease;
			}
			break;
		case LOnePress:
			if(PINA == 0x00){
				state = LOneRelease;
			}
			else{
				state = LOnePress;
			}
			break;
		case LOneRelease:
			if(PINA == 0x00){
				state = LOneRelease;
			}
			else{
				state = LZeroPress;
			}
			break;
		default:
			break;
	}
	
	switch(state){
		case Start:
			PORTB = 0x01;
		break;
		case LZeroPress:
			PORTB = 0x01;
		break;
		case LZeroRelease:
			PORTB = 0x01;
		break;
		case LOnePress:
			PORTB = 0x02;
		break;
		case LOneRelease:
			PORTB = 0x02;
		break;
		default:
		break;
	}
}

int main(void) {
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFF;PORTB = 0x01;
    /* Insert DDR and PORT initializations */
	state = Start;
    /* Insert your solution below */
    while (1) {
		Tick();
    }
    return 1;
}
