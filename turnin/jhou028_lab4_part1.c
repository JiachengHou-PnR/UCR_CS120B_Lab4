/*	Author: houjiacheng
 *	Lab Section: 022
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, S0_r, S0_p, S1_r, S1_p} state;

unsigned char tmpPA0;
unsigned char tmpPB0, tmpPB1;

void Tick() {

    switch (state)      // Transitions
    {
    case Start:
        state = S0_p;
        break;
    
    case S0_p:
        state = (tmpPA0) ? S0_p : S0_r;
        break;

    case S0_r:
        state = (tmpPA0) ? S1_p : S0_r;
        break;

    case S1_p:
        state = (tmpPA0) ? S1_p : S1_r;
        break;

    case S1_r:
        state = (tmpPA0) ? S0_p : S1_r;
        break;
    
    default:
        state = S0_p;
        break;
    }

    switch (state)      // State Actions
    {
    case Start: break;
    
    case S0_p:
        tmpPB0 = 1;
        tmpPB1 = 0;
        break;

    case S0_r:  
        tmpPB0 = 1;
        tmpPB1 = 0;
        break;

    case S1_p:
        tmpPB0 = 0;
        tmpPB1 = 1;
        break;

    case S1_r:  
        tmpPB0 = 0;
        tmpPB1 = 1;
        break;
    
    default:    break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    // Inputs
    DDRA = 0x00; PORTA = 0xFF;

    // Outputs
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    tmpPA0 = PINA & 0x01;
    tmpPB0 = 0x00; tmpPB1 = 0x00;

    state = Start;

    while (1) {
        tmpPA0 = PINA & 0x01;
        tmpPB0 = 0x00; tmpPB1 = 0x00;

        Tick();

        PORTB = tmpPB1 << 1 | tmpPB0;
    }

    

    return 1;
}
