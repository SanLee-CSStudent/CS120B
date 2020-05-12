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
#include "timer.h"
#include "simAVRHeader.h"
#include "stdio.h"
#endif

const double keys[8] = {261.63, 293.66, 329.63, 349.19, 392.00, 440.00, 493.88, 523.25};
const double beat[4] = {8, 4, 2, 1};
const char beats[200] = {4, 4, 4, 4, 8, 8, 8, 
1, 1, 1, 1, 1, 1, 1, 1, 
6, 4, 2, 2, 2, 4, 4, 4, 4, 3, 3, 4, 3, 3, 
8, 4, 4, 100, 3, 3, 4, 2, 2, 2, 4, 4, 4, 4, 
3, 3, 4, 3, 3, 8, 100, 4, 4, 6, 4, 2, 2, 2,
4, 4, 4, 4, 3, 3, 4, 3, 3, 
4, 4, 4, 4, 3, 3, 4, 2, 2, 2, 4, 4, 4, 4,
3, 3, 4, 3, 3, 8, 8,
3, 100, 3, 4, 2, 2, 2, 4, 4, 100, 4, 4, 3, 3, 4, 100, 2, 2, 2,
4, 4, 4, 4, 3, 100, 3, 3, 2, 100, 1, 2, 2};
const double melody[200] = {440.00, 329.628, 440.00, 783.991, 739.989, 493.883, 0, 0,
440, 493.883, 554.365, 622.254, 659.255, 739.989, 830.609,
440, 329.628, 277.183, 293.665, 329.628, 349.19, 440, 587.33, 698.456, 554.365, 587.33, 554.365, 440, 329.628, 
349.19, 587.33, 698.456, 587.33, 659.255, 554.365, 440, 329.628, 277.183, 329.628, 349.19, 440, 587.33, 493.883,
554.365, 587.33, 554.365, 440, 659.255, 587.33, 659.255, 698.456, 587.33, 880, 659.255, 440, 493.883, 554.365, 
349.19, 440, 587.33, 698.456, 554.365, 587.33, 554.365, 440, 329.628, 
349.19, 440, 587.33, 698.456, 659.255, 554.365, 440, 329.628, 277.183, 329.628, 349.19, 440, 587.33, 493.883,
554.365, 587.33, 659.255, 554.365, 440, 493.883, 587.33,
0, 1046.5, 1174.66, 987.767, 783.991, 659.255, 783.991, 698.456, 880, 987.767, 1046.5, 880, 987.767, 1046.5, 987.767, 698.456, 783.991, 659.255, 783.991,
698.456, 783.991, 1046.5, 783.991, 0, 1046.5, 1174.66, 987.767, 783.991, 0, 783.991, 659.255, 783.991, -1};
unsigned char tick = 0x00;
unsigned char EndFlag = 0x00;
unsigned char i = 0x10;
unsigned char j = 0x00;
unsigned char button = 0x00;
unsigned char PauseFlag = 0x00;
enum STATE{Start, Init, Wait, IncKey, IncKeyR, DecKey, DecKeyR, Play, PlayR, Pause, PauseR} states;

void set_PWM(double frequency){
    static double current_frequency;

    if(frequency != current_frequency){
        if(!frequency){
            TCCR3B &= 0x08;
        }
        else{
            TCCR3B |= 0x03;
        }

        if(frequency < 0.954){
            OCR3A = 0xFFFF;
        }
        else if(frequency > 31250){
            OCR3A = 0x0000;
        }
        else{
            OCR3A = (short) (8000000 / (2 * 128 * frequency)) - 1;
        }

        TCNT3 = 0;
        current_frequency = frequency;
    }
}

void PWM_on(){
    TCCR3A = (1 << COM3A0);

    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);

    set_PWM(0);
}

void PWM_off(){
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

void Tick(){
    switch (states){
        case Start:
            states = Init;
            break;
        
        case Init:
            states = Wait;
            break;

        case Wait:
            if(button == 0x01){
                states = IncKey;
            }
            else if(button == 0x02){
                states = DecKey;
            }
            else if(button == 0x04){
                states = Play;
            }
            else if(button == 0x08){
                states = Pause;
            }
            else{
                states = Wait;
            }
            break;

        case IncKey:
            if(button){
                states = IncKey;
            }
            else{
                states = IncKeyR;
            }
            break;

        case IncKeyR:
            states = Wait;
            break;

        case DecKey:
            if(button == 0x02){
                states = DecKey;
            }
            else{
                states = DecKeyR;
            }
            break;

        case DecKeyR:
            states = Wait;
            break;

        case Play:
            if(button == 0x04){
                states = Play;
            }
            else{
                states = PlayR;
            }

            break;

        case PlayR:
            if(beats[j] == -1){
                states = Wait;
            }

            if(tick >= beats[j]){
                
                j++;
                tick = 0;
            }

            if(EndFlag == 0x01){
                states = Wait;
                EndFlag = 0x00;
            }
            states = PlayR;
            break;

        case Pause:
            if(button == 0x08){
                states = Pause;
            }
            else{
                states = PauseR;
            }
            break;
        
        case PauseR:
            PauseFlag = !PauseFlag;
            break;

        default:
            break;
    }

    switch (states){
        case Start:

            break;
        
        case Init:

            break;

        case Wait:

            break;

        case IncKey:
            
            break;

        case IncKeyR:
            i++;
            set_PWM(keys[i % 8]);
            break;

        case DecKey:
            
            break;

        case DecKeyR:
            i--;
            set_PWM(keys[i % 8]);
            break;

        case Play:
            j = 0x00;
            break;

        case PlayR:
            if(j >= 200){
                EndFlag = 0x01;
                break;
            }

            if(beats[j] == 100){
                set_PWM(melody[j]);
                j++;
                break;
            }
            set_PWM(melody[j]);
            
            tick++;
            break;

        case Pause:

            break;

        case PauseR:
            if(PauseFlag){
                set_PWM(0);
            }
            else{
                set_PWM(keys[i%8]);
            }
            break;

        default:
            break;
    }
}

/*void Translate(){
    FILE* sheet;

    while((sheet = fopen("Sheet Music.txt", "r")) != EOF){
        fscanf(sheet, "%s", melody);
    }
    

    printf("%s", melody[0]);
    fclose(sheet);
}*/

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    TimerOn();
    TimerSet(112);
    PWM_on();

    states = Start;

    while (1) {
        button = ~PINA & 0x0F;

        Tick();

        while(!TimerFlag){}
        TimerFlag = 0x00;
        
    }
    PWM_off();
    return 1;
}
