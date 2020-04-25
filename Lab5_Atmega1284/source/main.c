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

enum STATE{Start, Init, stage0, stage1, stage2, stage3, stage4, stage5, r0, r1, r2, r3, r4, r5, r6} state;
unsigned char LED = 0x00;
unsigned char button = 0x00;

void Tick(){
	
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
            if(button){
                state = r0;
            }
            else{
                state = Init;
            }
			break;

        case r0:
            if(!button){
                state = stage0;
            }
            else{
                state = r0;
            }
            break;

		case stage0:
            if(button){
                state = r1;
            }
            else{
                state = stage0;
            }
			break;

        case r1:
            if(!button){
                state = stage1;
            }
            else{
                state = r1;
            }
            break;

        case stage1:
            if(button){
                state = r2;
            }
            else{
                state = stage1;
            }
			break;

        case r2:
            if(!button){
                state = stage2;
            }
            else{
                state = r2;
            }
            break;

        case stage2:
            if(button){
                state = r3;
            }
            else{
                state = stage2;
            }
			break;

        case r3:
            if(!button){
                state = stage3;
            }
            else{
                state = r3;
            }
            break;

        case stage3:
            if(button){
                state = r4;
            }
            else{
                state = stage3;
            }
			break;

        case r4:
            if(!button){
                state = stage4;
            }
            else{
                state = r4;
            }
            break;

        case stage4:
            if(button){
                state = r5;
            }
            else{
                state = stage4;
            }
			break;

        case r5:
            if(!button){
                state = stage5;
            }
            else{
                state = r5;
            }
            break;

        case stage5:
            if(button){
                state = r6;
            }
            else{
                state = stage5;
            }
			break;

        case r6:
            if(!button){
                state = Init;
            }
            else{
                state = r6;
            }
            break;
		default:
			break;
	}
	
	switch(state){
		case Start:
			LED = 0x00;
			break;

		case Init:
            LED = 0x00;
			break;

		case stage0:
            LED = LED | 0x01;
			break;

        case stage1:
            LED = LED | 0x04;
			break;

        case stage2:
            LED = LED | 0x10;
			break;

        case stage3:
            LED = LED | 0x02;
			break;

        case stage4:
            LED = LED | 0x08;
			break;

        case stage5:
            LED = LED | 0x20;
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
        button = ~PINA & 0x01;
		Tick();
        PORTC = LED;
    }
    return 1;
}
