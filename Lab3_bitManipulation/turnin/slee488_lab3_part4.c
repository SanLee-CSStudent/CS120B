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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFE;PORTB = 0x00;
    /* Insert your solution below */
	unsigned char weight;
	unsigned char overflow;
	unsigned char output;
	
    while (1) {
		weight = PINA;
		overflow = PINB & 0x01;
		output = PINB & 0x07;
		
		if((weight > 0x46) || (overflow == 0x01)){
			PORTB = output | 0x02;
		}
		else if(weight > 0x05){
			
			PORTB = output | 0x04;
		}
		else{
			PORTB = output & 0x01;
		}

    }
    return 1;
}
