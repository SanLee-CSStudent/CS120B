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
#include "io.h"
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

enum STATE{Start, ONE, TWO, THREE, FOUR, PRESS, RESUMEPRESS, RESUMERELEASE, RELEASE, VICTORY} states;
unsigned char LEDC = 0x00;
unsigned char button = 0x00;
unsigned char press = 0x00;
unsigned char score = 0x05;
unsigned char tick = 0x00;

void stayLit(int );

void Tick(){

    switch(states){
        case Start:
            states = ONE;
            break;

        case ONE:
            
            if(button){
                if(press == 0x01){
                    states = TWO;
                }
                else{
                    states= PRESS;
                    if(score > 0){
                        score--;
                    }
                    
                }
            }
            else{
                press = 0x00;
                states = TWO;
            }
            
            break;

        case TWO:

            if(button){
                if(press == 0x01){
                    states = THREE;
                }
                else{
                    states= PRESS;
                    if(score < 9){
                        score++;
                    }

                    if(score == 9){
                        states = VICTORY;
                    }

                }
            }
            else{
                press = 0x00;
                states = THREE;
            }

            break;

        case THREE:

            if(button){
                if(press == 0x01){
                    states = FOUR;
                }
                else{
                    states= PRESS;
                    if(score > 0){
                        score--;
                    }
                }
            }
            else{
                states = FOUR;
                press = 0x00;
            }

            break;
        
        case FOUR:
            
            if(button){
                if(press == 0x01){
                    states = ONE;
                }
                else{
                    states= PRESS;
                    if(score < 9){
                        score++;
                    }

                    if(score == 9){
                        states = VICTORY;
                    }
                }
            }
            else{
                states = ONE;
                press = 0x00;
            }

            break;
        
        case PRESS:
            if(button){
                states = PRESS;
            }
            else {
                states = RELEASE;
            }
            break;

        case RELEASE:
            if(button){
                states = ONE;
                press = 0x01;
            }
            else{
                states = RELEASE;
            }

            break;

        case RESUMEPRESS:
            states = ONE;

            break;

        case RESUMERELEASE:
            states = ONE;
            
            break;

        case VICTORY:
            states = VICTORY;
            break;

        default:
            break;
    }

    switch(states){
        case Start:
            break;

        case ONE:
            LEDC = 0x01;
            break;

        case TWO:
            LEDC = 0x02;
            break;

        case THREE:
            LEDC = 0x04;
            break;

        case FOUR:
            LEDC = 0x02;
            break;
        
        case PRESS:
            LCD_ClearScreen();
            LCD_WriteData(score + '0');
            break;

        case RELEASE:

            break;
        
        case VICTORY:
            if(tick % 8 == 0){
                // LCD_ClearScreen();
                LCD_DisplayString(1, "V");
            }
            else if(tick % 8 == 1){

                LCD_DisplayString(2, "I");
            }
            else if(tick % 8 == 2){

                LCD_DisplayString(3, "C");
            }
            else if(tick % 8 == 3){

                LCD_DisplayString(4, "T");
            }
            else if(tick % 8 == 4){

                LCD_DisplayString(5, "O");
            }
            else if(tick % 8 == 5){

                LCD_DisplayString(6, "R");
            }
            else if(tick % 8 == 6){

                LCD_DisplayString(7, "Y");
            }
            else{

                LCD_ClearScreen();
            }

            tick++;
            break;

        default:
            break;
    }

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    states = Start;

    TimerSet(300);
    TimerOn();

    LCD_init();

    LCD_ClearScreen();
    LCD_WriteData(score + '0');

    /* Insert your solution below */
    while (1) {
        button = (~PINA) & 0x01;
        Tick();
        PORTB = LEDC;
        while(!TimerFlag){}
        TimerFlag = 0;
    }
    return 1;
}
