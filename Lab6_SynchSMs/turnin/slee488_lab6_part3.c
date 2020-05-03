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
#include "timer.h"
#endif

enum STATE{Start, Init, Inc, Dec, IncR, DecR, ResetR, Reset} state;
unsigned char button = 0x00;
unsigned char i = 0x00;
unsigned char pressing = 0x00;

void Tick(){
	
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if(button == 0x01){
				state = Inc;
			}
			else if(button == 0x02){
				state = Dec;
			}
			else if(button == 0x03){
				state = Reset;
			}
			else {
				state = Init;
			}

			break;
		case Inc:
			// unsigned char tempA = (PINA & 0x01);
            if(!button && pressing){
                pressing = 0x00;
                state = Init;
            }

            if(button == 0x01){
                state = Inc;
                pressing = 0x01;
            }
            else if(button == 0x03){
                state = Reset;
            }
            else{
			    state = IncR;
            }
			
			break;
		case IncR:
			state = Init;
			
			break;

		case Dec:
			// unsigned char tempB = (PINA & 0x02);
            if(!button && pressing){
                pressing = 0x00;
                state = Init;
            }

			if(button == 0x02){
                pressing = 0x01;
				state = Dec;
			}
            else if(button == 0x03){
                state = Reset;
            }
			else{
				state = DecR;
			}
			break;

		case DecR:
			state = Init;
			
			break;

        case Reset:
            if(button == 0x03){
                state = Reset;
            }
            else{
                state = ResetR;
            }
            break;

		case ResetR:
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

		break;
		case Inc:
            i++;
            if(i == 10){
                i = 0;
                if(PORTC < 9){
                    PORTC++;
                }
                
            }

		break;
        
        case IncR:
            if(PORTC < 9){
                PORTC++;
            }
            break;
        
		case Dec:
            i++;
            if(i == 10){
                i = 0;
                if(PORTC > 0){
                    PORTC--;
                }
            }
        
		break;

        case DecR:
            if(PORTC > 0){
                PORTC--;
            }
            break;

		case ResetR:
			PORTC = 0x00;
		break;
		default:
			
		break;
	}
}

int main(void) {
	DDRA = 0x00;PORTA = 0xFF;
	DDRC = 0xFF;PORTC = 0x07;
    /* Insert DDR and PORT initializations */
	state = Start;
    /* Insert your solution below */
    TimerSet(100);
    TimerOn();

    while (1) {
		button = ~PINA & 0x03;
		Tick();
        while(!TimerFlag){}
        TimerFlag = 0;
    }
    return 1;
}
