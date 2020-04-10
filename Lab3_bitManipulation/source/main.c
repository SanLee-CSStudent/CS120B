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
	DDRD = 0x00;PORTD = 0xFF;
	DDRB = 0xFE;PORTB = 0x00;
    /* Insert your solution below */
	unsigned char weight;
	// unsigned char output;
	unsigned char one;
	
    while (1) {

		one = PINB & 0x01;
		if(weight != 0xFE){
			weight = PIND + one;
		}
		else{
			weight = PIND;
		}
		
		if(weight > 0x46){
			PORTB = 0x02;
		}
		else if(weight >= 0x05){
			
			PORTB = 0x04;
		}

		PORTB = PORTB & 0x06;

    }
    return 1;
}
