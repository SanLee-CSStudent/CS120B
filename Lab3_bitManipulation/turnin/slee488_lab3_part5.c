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
	DDRB = 0xFE;PORTB = 0x01;
    /* Insert your solution below */
	unsigned char weight;
	// unsigned char output;
	unsigned char one;
	
    while (1) {

		one = PINB & 0x01;
		if(weight != 0xFF){
			weight = PIND + one;
		}
		
		if((PIND >= 0x46) || (PIND == 0x45 && one == 1)){
			PORTB = 0x02;
		}
		else if(PIND > 0x05 || (PIND == 5 && one == 1)){
			
			PORTB = 0x04;
		}
		else{
			PORTB = 0x00;
		}

    }
    return 1;
}
