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

unsigned short input;
unsigned short max = 0x00C3;
unsigned char upper;
unsigned char lower;
unsigned char LED;

void ADC_init(){    
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */

    ADC_init();
    while (1) {
        input = ADC;
        if(input < (max/8)){
            LED = 0x00;
        }
        else if(input < (max/4)){
            LED = 0x01;
        }
        else if(input < (3*max / 8)){
            LED = 0x03;
        }
        else if(input < (max / 2)){
            LED = 0x07;
        }
        else if(input < (5*max / 8)){
            LED = 0x0F;
        }
        else if(input < (3*max / 4)){
            LED = 0x1F;
        }
        else if(input < (7*max/8)){
            LED = 0x3F;
        }
        else{
            LED = 0x7F;
        }
        
        PORTC = LED;
    }
    return 1;
}
