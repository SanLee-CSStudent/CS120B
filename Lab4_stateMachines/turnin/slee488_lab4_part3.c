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

enum STATE{Start, Init, PassPress, PassRelease, Open, Lock} state;

void Tick(){
	
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if(PINA == 0x04){
				state = PassPress;
			}
			else if(PINA == 0x80){
				state = Lock;
			}
			else{
				state = Init;
			}
		
			break;
			
		case PassPress:
			if(PINA == 0x04){
				state = PassPress;
			}
			else{
				state = PassRelease;
			}
			break;
			
		case PassRelease:
			if(PINA == 0x02){
				state = Open;
			}
			else{
				state = Init;
			}
			break;
			
		case Open:
			state = Init;
			break;
			
		case Lock:
			state = Init;
			
			break;
			
		default:
			break;
	}
	
	switch(state){
		case Start:
			PORTB = 0x00;
			PORTC = 0x00;
			break;
		case Init:
			
			PORTC = 0x01;
			break;
		case PassPress:
			
			PORTC = 0x10;
			break;
		case PassRelease:
			
			PORTC = 0x11;
			break;
		case Open:
			PORTB = 0x01;
			PORTC = 0x02;
			break;
		case Lock:
			PORTB = 0x00;
			PORTC = 0x03;
			break;
		default:
			
			break;
	}
}

int main(void) {
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFF;PORTB = 0x00;
	DDRC = 0xFF;PORTC = 0x00;
    /* Insert DDR and PORT initializations */
	state = Start;
    /* Insert your solution below */
    while (1) {
		Tick();
    }
    return 1;
}
