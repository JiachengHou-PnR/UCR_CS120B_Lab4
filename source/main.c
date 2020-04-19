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

enum States {Start, locked, u_step1, u_step2, unlocked, l_step1, l_step2} state;

unsigned char tmpA0, tmpA1, tmpA2, tmpA7;
unsigned char tmpB;

void Tick() {

    switch (state)      // Transitions
    {
    case Start:
        state = locked;
        break;

    case locked:
        tmpB = 0x00;
        if (tmpA2 && !(tmpA0 || tmpA1 || tmpA7))
        {
            state = u_step1;
        }
        else // (other / multiple keys)
        {
            state = locked;
        }
        break;

    case u_step1:
        if (tmpA2 && !(tmpA0 || tmpA1 || tmpA7))
        {
            state = u_step1;
        }
        else if (!tmpA2 && !(tmpA0 || tmpA1 || tmpA7))
        {
            state = u_step2;
        }
        else // (other / multiple keys)
        {
            state = locked;
        }
        break; 

    case u_step2:
        if (!tmpA2 && !(tmpA0 || tmpA1 || tmpA7))
        {
            state = u_step2;
        }
        else if (tmpA1 && !(tmpA0 || tmpA2 || tmpA7))
        {
            state = unlocked;
        }
        else // (other / multiple keys)
        {
            state = locked;
        }
        break; 
        
    case unlocked:
        if (tmpA7 && !(tmpA0 || tmpA1 || tmpA2))
        {
            state = locked;
        }
        else if (tmpA2 && !(tmpA0 || tmpA1 || tmpA7))
        {
            state = l_step1;
        }
        else // (other / multiple keys)
        {
            state = unlocked;
        }
        break;

    case l_step1:
        if (tmpA2 && !(tmpA0 || tmpA1 || tmpA7))
        {
            state = l_step1;
        }
        else if (!tmpA2 && !(tmpA0 || tmpA1 || tmpA7))
        {
            state = l_step2;
        }
        else // (other / multiple keys)
        {
            state = unlocked;
        }
        break; 

    case l_step2:
        if (!tmpA2 && !(tmpA0 || tmpA1 || tmpA7))
        {
            state = l_step2;
        }
        else if (tmpA1 && !(tmpA0 || tmpA2 || tmpA7))
        {
            state = locked;
        }
        else // (other / multiple keys)
        {
            state = unlocked;
        }
        break;

    default:
        state = locked;
        break;
    }

    switch (state)      // State Actions
    {
    case Start:     break;
    
    case locked:    
        tmpB = 0x00;
        break;

    case u_step1:   break;

    case u_step2:   break;

    case l_step1:   break;

    case l_step2:   break;
    
    case unlocked:  
        tmpB = 0x01;
        break;

    default:        break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    // Inputs
    DDRA = 0x00; PORTA = 0xFF;

    // Outputs
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    tmpB = 0x00;
    state = Start;

    while (1) {
        tmpA0 =  PINA & 0x01;
        tmpA1 = (PINA >> 1) & 0x01;
        tmpA2 = (PINA >> 2) & 0x01;
        tmpA7 = (PINA >> 7) & 0x01;

        Tick();

        PORTB = tmpB;
        PORTC = state;
    }
    
    return 1;
}
