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
#include "queue.h"
#endif

#include <avr/interrupt.h>
#include <stdlib.h>

unsigned char button = 0x00;
signed char location = 1;
unsigned char pause = 0x00;

typedef struct task{
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);
} task;

enum DISPLAY_STATES {DS_Start, DS_Wait, DS_Pause} DS_states;

int DS_Tick(int state){
    static unsigned char displacement = 16;
    static unsigned char i = 0x00;
    switch(state){
        case DS_Start:
            state = DS_Wait;
            break;

        case DS_Wait:
            if(pause){
                state = DS_Pause;
            }
            else{
                state = DS_Wait;
            }

            break;

        case DS_Pause:
            if(pause){
                state = DS_Pause;
            }
            else{
                state = DS_Wait;
            }
            break;

        default:
            break;
    }

    switch(state){
        case DS_Start:
            break;

        case DS_Wait:
            i++;

            LCD_Cursor(displacement+1);
            LCD_WriteData(' ');       
            LCD_Cursor(displacement);
            LCD_WriteData('#');
            LCD_Cursor(location);
            if(displacement > 0){
                displacement--;
            }
            break;

        case DS_Pause:

            break;

        default:
            break;
    }

    return state;
}

unsigned char input;

enum KEYPAD_STATE{KS_Start, KS_Wait, KS_PausePress, KS_PauseRelease, KS_PauseOffPress} KS_states;

int KS_Tick(int state){
    unsigned char key = 0x00;
    input = GetKeypadKey();
    switch(state){
        case KS_Start:
            state = KS_Wait;
            break;

        case KS_Wait:
            if(button == 0x04){
                state = KS_PausePress;
            }
            else{
                state = KS_Wait;
            }
            break;

        case KS_PausePress:
            if(button == 0x04){
                state = KS_PausePress;
            }
            else{
                state = KS_PauseRelease;
            }
            break;

        case KS_PauseRelease:
            if(button == 0x04){
                state = KS_PauseOffPress;
            }
            else{
                state = KS_PauseRelease;
            }
            break;

        case KS_PauseOffPress:
            if(button == 0x04){
                state = KS_PauseOffPress;
            }
            else{
                pause = 0x00;
                state = KS_Wait;
            }
            break;

        default:

            break;
    }

    switch(state){
        case KS_Start:

            break;

        case KS_Wait:
            pause = 0x00;
            if(button == 0x01){
                location = 1;

            }
            else if(button == 0x02){
                location = -1;
                
            }

            LCD_Cursor(location);
            break;
        
        case KS_PausePress:
            pause = 0x01;
            break;

        default:

            break;
    }

    return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    unsigned char k = 0x00;

    LCD_init();
    LCD_ClearScreen();
    // LCD_DisplayString(1, "Congratulations!");
    LCD_Cursor(1);

    static Queue obstables = QueueInit(8);

    static task DS_task;
    DS_task.state = DS_Start;
    DS_task.period = 300;
    DS_task.elapsedTime = DS_task.period;
    DS_task.TickFct = &DS_Tick;

    static task KS_task;
    KS_task.state = KS_Start;
    KS_task.period = 50;
    KS_task.elapsedTime = KS_task.period;
    KS_task.TickFct = &KS_Tick;

    const unsigned char taskNum = 2;
    task *tasks[] = { &DS_task, &KS_task };

    TimerSet(50);
    TimerOn();

    while (1) {
        button = (~PINA) & 0x07;

        for(k = 0; k < taskNum; k++){
            if(tasks[k]->elapsedTime == tasks[k]->period){
                tasks[k]->state = tasks[k]->TickFct(tasks[k]->state);
                tasks[k]->elapsedTime = 0;
            }
        }

        while(!TimerFlag);
        TimerFlag = 0;
 
        for(k = 0; k < taskNum; k++){
            tasks[k]->elapsedTime += 50;
        }

    }
    return 1;
}
