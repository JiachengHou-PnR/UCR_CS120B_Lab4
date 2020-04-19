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

enum States {Start, init, wait, increment, decrement, reset} state;

unsigned char tmpA0, tmpA1;
unsigned char tmpC;

void Tick() {

    switch (state)      // Transitions
    {
    case Start:
        state = init;
        break;

    case init:
        tmpC = 0x07;
        state = wait;
        break;

    case wait:
        if (tmpA0 && tmpA1)
        {
            state = reset;
        }
        else if (!tmpA0 && !tmpA1)
        {
            state = wait;
        }
        else if (tmpA0 && !tmpA1)
        {
            if (tmpC < 9) tmpC++;
            state = increment;
        }
        else // (!tmpA0 && tmpA1)
        {
            if (tmpC > 0) tmpC--;
            state = decrement;
        }
        break;        

    case increment:
        if (tmpA0 && tmpA1)
        {
            state = reset;
        }
        else if (tmpA0 && !tmpA1)
        {
            state = increment;
        }
        else // (!tmpA0)
        {
            state = wait;
        }
        break;
        
    case decrement:
        if (tmpA0 && tmpA1)
        {
            state = reset;
        }
        else if (!tmpA0 && tmpA1)
        {
            state = decrement;
        }
        else // (!tmpA1)
        {
            state = wait;
        }
        break;

    case reset:
        if (!tmpA0 && !tmpA1)
        {
            state = wait;
        }
        else // !(!tmpA0 && !tmpA1)
        {
            state = reset;
        }
        break;
    
    default:
        state = init;
        break;
    }

    switch (state)      // State Actions
    {
    case Start:     break;
    
    case init:      break;

    case wait:      break;

    case increment: break;
    
    case decrement: break;

    case reset:
        tmpC = 0;
        break;

    default:        break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    // Inputs
    DDRA = 0x00; PORTA = 0xFF;

    // Outputs
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    tmpC = 0x00;
    state = Start;

    while (1) {
        tmpA0 =  PINA & 0x01;
        tmpA1 = (PINA & 0x02) >> 1;

        Tick();

        PORTC = tmpC;
    }

    

    return 1;
}
