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
unsigned char startSingle = 0x00;
unsigned char gameover = 0x00;
unsigned char reset = 0x00;
unsigned char score = 0;
unsigned char bulletDisplacement = 0;
char string[] = {'D', 'I', 'S', 'T', 'A', 'N', 'C', 'E', ':', ' '};

static Queue obstacles;

typedef struct task{
    int state;
    unsigned long period;
    unsigned long elapsedTime;
    int (*TickFct)(int);
} task;

typedef struct stone{
    signed char displacement;
    signed char sLoc;
    unsigned char end;
    unsigned char destoryable;
} stone;

enum MENU {M_Start, M_Wait, M_SingleClear, M_Single} M_states;

int M_Tick(int state){

    switch(state){
        case M_Start:
            reset = 0;
            startSingle = 0;
            state = M_Wait;
            break;

        case M_Wait:
            state = M_Wait;

            if(button == 0x01){
                state = M_SingleClear;
            }

            break;

        case M_SingleClear:
            if(button == 0x01){
                state = M_SingleClear;
            }
            else {
                state = M_Single;
            }
            
            break;

        case M_Single:
            state = M_Single;
            
            if(button == 0x08){
                reset = 1;
                startSingle = 0;
                state = M_Start;
            }
            break;

        default:
            break;
    }

    switch(state){
        case M_Start:

            break;

        case M_Wait:
            
            break;

        case M_SingleClear:
            LCD_ClearScreen();
            LCD_Cursor(1);
            break;

        case M_Single:

            startSingle = 1;
            break;

        default:
            break;
    }

    return state;
}

enum REPLENISH_OBSTACLE {RO_Start, RO_Init, RO_Wait} RO_states;

int RO_Tick(int state){
    unsigned char random;

    switch(state){
        case RO_Start:
            state = RO_Init;
            break;

        case RO_Init:
            if(startSingle){
                state = RO_Wait;
            }
            else{
                state = RO_Init;
            }
            break;

        case RO_Wait:    
            state = RO_Wait;
            
            break;

        default:

            break;
    }

    switch(state){
        case RO_Start:

            break;

        case RO_Wait:
            if(!QueueIsFull(obstacles)){
                random = rand() % 2;
                QueueEnqueue(obstacles, random);
            }
            break;

        default:

            break;
    }

    return state;
}

stone stones[8];
unsigned size = 8;
unsigned max = 0;
unsigned curr = 0;
unsigned char delay = 0;
unsigned char maxDelay = -1;

enum DISPLAY_STATES {DS_Start, DS_Init, DS_Wait, DS_Pause} DS_states;

int DS_Tick(int state){
    unsigned char loc = 0x00;
    unsigned char i = 0;
    
    stone s;
    if(score < 30){
        maxDelay = (rand() % 8) + 4;
    }
    else if(score < 100){
        maxDelay = (rand() % 4) + 3;
    }
    else{
        maxDelay = (rand() % 2) + 2;
    }
    
    switch(state){
        case DS_Start:
            s.displacement = 0;
            s.end = 0;
            s.sLoc = 0;
            s.destoryable = rand() % 2;
            for(i=0; i<size; i++){

                stones[i] = s;
                curr = 0;
            }

            state = DS_Init;
            break;

        case DS_Init:
            if(startSingle){
                state = DS_Wait;
            }
            else{
                state = DS_Init;
            }
            break;

        case DS_Wait:
            if(pause || gameover){
                state = DS_Pause;
            }
            else{
                state = DS_Wait;
            }

            break;

        case DS_Pause:
            if(pause || gameover){
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
            if(delay > maxDelay){
                if(size > curr){
                    loc = QueueDequeue(obstacles);
                    s.end = 0;

                    if(!loc){
                        s.displacement = 32;
                        s.sLoc = 1;
                    }
                    else{
                        s.displacement = 16;
                        s.sLoc = 0;
                    }

                    s.destoryable = rand() % 2;
                    stones[curr] = s;
                    curr++;
                }
                
                if(curr < size && max != size){
                    max = curr + 1;
                }
                else{
                    max = size;
                }
                delay = 0;
                maxDelay = (rand() % 8) + 4;
            }
            
            for(i = 0; i < max; i++){
                LCD_Cursor(stones[i].displacement+1);
                LCD_WriteData(' ');       
                LCD_Cursor(stones[i].displacement);
                if(stones[i].destoryable){
                    LCD_WriteData('#');
                }
                else{
                    LCD_WriteData('*');
                }
                LCD_Cursor(location);
                if(stones[i].sLoc){
                    if(stones[i].displacement > 17){
                        stones[i].displacement--;
                    }
                    else{
                        LCD_Cursor(17);
                        LCD_WriteData(' ');
                        stones[i].displacement = 0;
                        s.end = 1;
                        curr = i;
                    }
                }
                else{
                    if(stones[i].displacement > 0){
                        stones[i].displacement--;
                    }
                    else{
                        stones[i].displacement = 0;
                        s.end = 1;
                        curr = i;
                    }
                }
                
            }

            delay++;
            break;

        case DS_Pause:

            break;

        default:
            break;
    }

    return state;
}

unsigned char input;

enum KEYPAD_STATE{KS_Start, KS_Init, KS_Wait, KS_PausePress, KS_PauseRelease, KS_PauseOffPress, GAMEOVER} KS_states;

int KS_Tick(int state){
    static unsigned char displayGO = 0x01;
    unsigned char ones;
    unsigned char digit;
    unsigned char l;
    unsigned char temp;

    input = GetKeypadKey();
    switch(state){
        case KS_Start:
            state = KS_Init;
            displayGO = 1;
            break;
        
        case KS_Init:
            if(startSingle){
                state = KS_Wait;
            }
            else{
                state = KS_Init;
            }
            break;

        case KS_Wait:
            if(button == 0x04){
                state = KS_PausePress;
            }
            else if(button == 0x08){
                reset = 1;
                startSingle = 0;
                state = KS_Start;
            }
            else{
                state = KS_Wait;
            }

            if(gameover){
                state = GAMEOVER;
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

        case GAMEOVER:
            if(button == 0x08){
                reset = 1;
                startSingle = 0;
                state = KS_Start;
            }
            else{
                state = GAMEOVER;
            }
            break;

        default:

            break;
    }

    switch(state){
        case KS_Start:
            gameover = 0;
            LCD_Cursor(1);
            break;

        case KS_Init:
            break;

        case KS_Wait:
            pause = 0x00;
            if(button == 0x01){
                location = 1;
            }
            else if(button == 0x02){
                location = 17;
            }

            LCD_Cursor(location);
            
            for(l = 0; l < max; l++){
                if(stones[l].displacement == location){
                    gameover = 1;
                    LCD_ClearScreen();
                    break;
                }
            }
            break;
        
        case KS_PausePress:
            pause = 0x01;
            break;

        case GAMEOVER:
            if(displayGO == 1){
                LCD_Cursor(displayGO);
                LCD_WriteData('!');
            }
            else if(displayGO == 2){
                LCD_Cursor(displayGO);
                LCD_WriteData('!');
            }
            else if(displayGO == 3){
                LCD_Cursor(displayGO);
                LCD_WriteData('G');
            }
            else if(displayGO == 4){
                LCD_Cursor(displayGO);
                LCD_WriteData('A');
            }
            else if(displayGO == 5){
                LCD_Cursor(displayGO);
                LCD_WriteData('M');
            }
            else if(displayGO == 6){
                LCD_Cursor(displayGO);
                LCD_WriteData('E');
            }
            else if(displayGO == 7){
                LCD_Cursor(displayGO);
                LCD_WriteData(' ');
            }
            else if(displayGO == 8){
                LCD_Cursor(displayGO);
                LCD_WriteData('O');
            }
            else if(displayGO == 9){
                LCD_Cursor(displayGO);
                LCD_WriteData('V');
            }
            else if(displayGO == 10){
                LCD_Cursor(displayGO);
                LCD_WriteData('E');
            }
            else if(displayGO == 11){
                LCD_Cursor(displayGO);
                LCD_WriteData('R');
            }
            else if(displayGO == 12){
                LCD_Cursor(displayGO);
                LCD_WriteData('!');
            }
            else if(displayGO == 13){
                LCD_Cursor(displayGO);
                LCD_WriteData('!');
            }
            else {
                for(l = 0; l < 10; l++){
                    LCD_Cursor(l+1);
                    LCD_WriteData(string[l]);
                }

                temp = score;
                if(temp < 10){
                    LCD_Cursor(11);
                    LCD_WriteData('0');
                    LCD_Cursor(12);
                    LCD_WriteData('0');
                    LCD_Cursor(13);
                    LCD_WriteData(temp + '0');
                }
                else if(temp < 100){
                    LCD_Cursor(11);
                    LCD_WriteData('0');
                    digit = temp / 10;
                    temp = temp % 10;
                    LCD_Cursor(12);
                    LCD_WriteData(digit + '0');
                    LCD_Cursor(13);
                    LCD_WriteData(temp + '0');
                }
                else if(temp < 1000){
                    digit = temp / 100;
                    temp = temp % 100;
                    LCD_Cursor(11);
                    LCD_WriteData(digit + '0');
                    digit = temp / 10;
                    temp = temp % 10;
                    LCD_Cursor(12);
                    LCD_WriteData(digit + '0');
                    LCD_Cursor(13);
                    LCD_WriteData(temp + '0');
                }
                else{
                    LCD_DisplayString(1, "VICTORY 1000m!");
                }
                
                LCD_Cursor(14);
                LCD_WriteData('m');
            }

            displayGO = displayGO + 1;
            break;

        default:

            break;
    }

    return state;
}

enum BULLET_STATE {BS_Start, BS_Init, BS_Wait, BS_Pause, BS_Fly} BS_states;

int BS_Tick(int state){
    static unsigned char bulletFly = 0;
    unsigned char m = 0;

    switch(state){
        case BS_Start:
            state = BS_Init;
            break;

        case BS_Init:
            if(startSingle){
                state = BS_Wait;
            }
            else{
                state = BS_Init;
            }
            break;

        case BS_Wait:
            if(button == 0x10){
                state = BS_Fly;
            }
            else{
                state = BS_Wait;
            }

            if(pause){
                state = BS_Pause;
            }

            break;

        case BS_Pause:
            if(pause){
                state = BS_Pause;
            }
            else{
                state = BS_Wait;
            }
            break;

        case BS_Fly:
            if(bulletFly){
                state = BS_Fly;
            }
            else{
                state = BS_Wait;
            }

            break;

        default:

            break;
    }

    switch(state){
        case BS_Start:

            break;

        case BS_Init:

            break;

        case BS_Wait:
            bulletDisplacement = location;
            if(button == 0x10){
                bulletFly = 1;
            }
            break;

        case BS_Pause:

            break;

        case BS_Fly:
            bulletFly = 1;
            LCD_Cursor(bulletDisplacement+1);
            LCD_WriteData('>');
            LCD_Cursor(bulletDisplacement);
            LCD_WriteData(' ');
            bulletDisplacement++;
            for(m=0; m<max; m++){
                if(stones[m].displacement == bulletDisplacement && stones[m].destoryable){
                    LCD_Cursor(bulletDisplacement);
                    LCD_WriteData(' ');
                    LCD_Cursor(bulletDisplacement+1);
                    LCD_WriteData(' ');
                    stones[m].displacement = 0;             
                    score += 10;
                    bulletFly = 0;
                    break;
                }
                else if(!stones[m].destoryable){
                    LCD_Cursor(bulletDisplacement);
                    LCD_WriteData('*');

                    bulletFly = 0;
                    break;
                }
            }
            
            if(bulletDisplacement == 17 || bulletDisplacement > 32){
                LCD_Cursor(bulletDisplacement);
                LCD_WriteData(' ');
                bulletFly = 0;
            }
            LCD_Cursor(location);
            break;

        default:

            break;
    }

    return state;
}

enum SCORE_STATE {SS_Start, SS_Init, SS_Wait, SS_Pause} SS_states;

int SS_Tick(int state){
    switch(state){
        case SS_Start:
            state = SS_Init;
            break;

        case SS_Init:
            if(startSingle){
                state = SS_Wait;
            }
            else{
                state = SS_Init;
            }
            break;

        case SS_Wait:

            if(pause || gameover){
                state = SS_Pause;
            }
            else{
                state = SS_Wait;
            }
            break;

        case SS_Pause:
            if(pause || gameover){
                state = SS_Pause;
            }
            else{
                state = SS_Wait;
            }

            break;
        default:
            break;
    }

    switch(state){
        case SS_Init:

            break;

        case SS_Wait:
            score++;
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
    LCD_Cursor(1);
    LCD_DisplayString(4, "LCD Racer");
    obstacles = QueueInit(8);

    static task M_task;
    M_task.state = M_Start;
    M_task.period = 50;
    M_task.elapsedTime = M_task.period;
    M_task.TickFct = &M_Tick;

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

    static task RO_task;
    RO_task.state = RO_Start;
    RO_task.period = 150;
    RO_task.elapsedTime = RO_task.period;
    RO_task.TickFct = &RO_Tick;

    static task SS_task;
    SS_task.state = SS_Start;
    SS_task.period = 300;
    SS_task.elapsedTime = SS_task.period;
    SS_task.TickFct = &SS_Tick;

    static task BS_task;
    BS_task.state = BS_Start;
    BS_task.period = 50;
    BS_task.elapsedTime = BS_task.period;
    BS_task.TickFct = &BS_Tick;

    const unsigned char taskNum = 6;
    task *tasks[] = {&M_task, &RO_task, &DS_task, &SS_task, &BS_task, &KS_task};

    TimerSet(50);
    TimerOn();

    while (1) {
        if(reset){
            LCD_ClearScreen();
            LCD_Cursor(1);
            LCD_DisplayString(4, "LCD Racer");
            
            score = 0;

            M_task.state = M_Start;
            DS_task.state = DS_Start;
            DS_task.period = 300;
            KS_task.state = KS_Start;
            RO_task.state = RO_Start;
            SS_task.state = SS_Start;
            BS_task.state = BS_Start;
        }

        button = (~PINA) & 0x1F;
        if(score < 25){
            DS_task.period = 300;
        }
        else if(score < 100){
            DS_task.period = 250;
        }
        else if(score < 250){
            DS_task.period = 200;
        }
        else{
            DS_task.period = 150;
        }

        for(k = 0; k < taskNum; k++){
            if(tasks[k]->elapsedTime >= tasks[k]->period){
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
