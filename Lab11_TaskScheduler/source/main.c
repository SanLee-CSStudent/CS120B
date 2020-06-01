/*	Author: lab
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
#include "timer.h"
#include "keypad.h"
#endif

#include <avr/interrupt.h>

typedef struct task{
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);
} task;

enum DISPLAY_STATES {DS_Start, DS_Wait} DS_states;

int DS_Tick(int state){
    

    switch(state){
        case DS_Start:
            state = DS_Wait;
            break;

        case DS_Wait:
            state = DS_Wait;
            break;

        default:
            break;
    }

    switch(state){
        case DS_Start:
            break;

        case DS_Wait:
            
            
            
            break;

        default:
            break;
    }

    return state;
}

unsigned char input;

enum KEYPAD_STATE{KS_Start, KS_Wait} KS_states;

int KS_Tick(int state){
    static unsigned char i = 0x01;

    switch(state){
        case KS_Start:
            state = KS_Wait;
            break;

        case KS_Wait:
            state = KS_Wait;
            break;
        
        default:

            break;
    }

    switch(state){
        case KS_Start:

            break;

        case KS_Wait:
            input = GetKeypadKey();

            switch(input){
                // case '\0': LCD_DisplayString(1, ""); break;
                case '0': LCD_DisplayString(i, ""); LCD_DisplayString(i, "0"); break;
                case '1': LCD_DisplayString(i, ""); LCD_DisplayString(i, "1"); break;
                case '2': LCD_DisplayString(i, ""); LCD_DisplayString(i, "2"); break;
                case '3': LCD_DisplayString(i, ""); LCD_DisplayString(i, "3"); break;
                case '4': LCD_DisplayString(i, ""); LCD_DisplayString(i, "4"); break;
                case '5': LCD_DisplayString(i, ""); LCD_DisplayString(i, "5"); break;
                case '6': LCD_DisplayString(i, ""); LCD_DisplayString(i, "6"); break;
                case '7': LCD_DisplayString(i, ""); LCD_DisplayString(i, "7"); break;
                case '8': LCD_DisplayString(i, ""); LCD_DisplayString(i, "8"); break;
                case '9': LCD_DisplayString(i, ""); LCD_DisplayString(i, "9"); break;
                case 'A': LCD_DisplayString(i, ""); LCD_DisplayString(i, "A"); break;
                case 'B': LCD_DisplayString(i, ""); LCD_DisplayString(i, "B"); break;
                case 'C': LCD_DisplayString(i, ""); LCD_DisplayString(i, "C"); break;
                case 'D': LCD_DisplayString(i, ""); LCD_DisplayString(i, "D"); break;
                case '*': LCD_DisplayString(i, ""); LCD_DisplayString(i, "*"); break;
                case '#': LCD_DisplayString(i, ""); LCD_DisplayString(i, "#"); break;
                default: break;
                
            }
            i++;
            break;
        
        default:

            break;
    }

    return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */

    LCD_init();
    LCD_ClearScreen();
    LCD_DisplayString(1, "Congratulations!");

    static task DS_task;
    DS_task.state = DS_Start;
    DS_task.period = 200;
    DS_task.elapsedTime = DS_task.period;
    DS_task.TickFct = &DS_Tick;

    static task KS_task;
    KS_task.state = KS_Start;
    KS_task.period = 200;
    KS_task.elapsedTime = KS_task.period;
    KS_task.TickFct = &KS_Tick;

    TimerSet(200);
    TimerOn();

    while (1) {

        if(DS_task.elapsedTime == DS_task.period){
            // DS_task.state = DS_task.TickFct(DS_task.state);
            DS_task.elapsedTime = 0;
        }

        if(KS_task.elapsedTime == KS_task.period){
            KS_task.state = KS_task.TickFct(KS_task.state);
            KS_task.elapsedTime = 0;
        }

        while(!TimerFlag);
        TimerFlag = 0;

        DS_task.elapsedTime += 200;
        KS_task.elapsedTime += 200;
    }
    return 1;
}
