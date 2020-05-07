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

#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B 	= 0x0B;	// bit3 = 1: CTC mode (clear timer on compare)
					// bit2bit1bit0=011: prescaler /64
					// 00001011: 0x0B
					// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
					// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A 	= 125;	// Timer interrupt will be generated when TCNT1==OCR1A
					// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
					// So when TCNT1 register equals 125,
					// 1 ms has passed. Thus, we compare to 125.
					// AVR timer interrupt mask register

	TIMSK1 	= 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1 = 0;

	// TimerISR will be called every _avr_timer_cntcurr milliseconds
	_avr_timer_cntcurr = _avr_timer_M;

	//Enable global interrupts
	SREG |= 0x80;	// 0x80: 1000000
}

void TimerOff() {
	TCCR1B 	= 0x00; // bit3bit2bit1bit0=0000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; 			// Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { 	// results in a more efficient compare
		TimerISR(); 				// Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

enum STATE{Start, Init, Inc, Dec, IncR, DecR, IncP, DecP, ResetR, Reset} state;
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
            if(button == 0x01){
                state = IncP;
                // pressing = 0x01;
            }
            else if(button == 0x03){
                state = Reset;
            }
            else{
			    state = IncR;
            }
			
			break;

		case IncP:
			if(button == 0x01){
                pressing = 0x01;
				state = IncP;
			}
			else{
				state = Init;
			}
			break;
		
		case IncR:
			state = Init;
			
			break;

		case Dec:
			// unsigned char tempB = (PINA & 0x02);
			if(button == 0x02){
				state = DecP;
			}
            else if(button == 0x03){
                state = Reset;
            }
			else{
				state = DecR;
			}
			break;

		case DecP:
			if(button == 0x02){
				state = DecP;
			}
			else{
				state = Init;
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
			PORTB = 0x07;
		break;
		case Init:

		break;

		case Inc:
	
			if(PORTB < 9){
				PORTB++;
			}
			
			break;

		case IncP:
            i += 1;
            if(i == 10){
                i = 0;
                if(PORTB < 9){
                    PORTB++;
                }
                
            }

		break;

		case IncR:
			
			break;
		
		case Dec:

			if(PORTB > 0){
				PORTB--;
			}
			
			break;

		case DecP:
            
            if(i == 10){
                i = 0;
                if(PORTB > 0){
                    PORTB--;
                }
            }
			i += 1;
        
		break;

		case DecR:
			
			break;

		case ResetR:
			PORTB = 0x00;
		break;
		default:
			
		break;
	}
}

int main(void) {
	DDRA = 0x00;PORTA = 0xFF;
	DDRB = 0xFF;PORTB = 0x07;
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
