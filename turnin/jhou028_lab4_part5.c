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

enum States {Start, locked, u_keyIn, unlocked, l_keyIn} state;

unsigned char tmpA, tmpA7;
unsigned char tmpB;
unsigned char inChars[4];
unsigned char keyChars[] = {4, 1, 2, 1};

void Tick() {

    switch (state)      // Transitions
    {
    case Start:
        state = locked;
        break;

    case locked:
        tmpB = 0x00;
        if (inChars == keyChars)
        {
            memset(&inChars[0], 0, sizeof(inChars));
            state = unlocked;
        }
        else if (tmpA)
        {
            for (unsigned char i = 1; i < 8; i++)
            {
                inChars[i] = inChars[i-1];
            }
            inChars[0] = tmpA;

            state = u_keyIn;
        }
        else // (other / multiple keys)
        {
            state = locked;
        }
        break;

    case u_keyIn:
        if (tmpA == inChars[0])
        {
            state = u_keyIn;
        }
        else // (other / multiple keys)
        {
            state = locked;
        }
        break; 
        
    case unlocked:
        if ((tmpA7 && !tmpA) || (inChars == keyChars))
        {
            memset(&inChars[0], 0, sizeof(inChars));
            state = locked;
        }
        else if (tmpA)
        {
            for (unsigned char i = 1; i < 8; i++)
            {
                inChars[i] = inChars[i-1];
            }
            inChars[0] = tmpA;

            state = l_keyIn;
        }
        else // (other / multiple keys)
        {
            state = unlocked;
        }
        break;

    case l_keyIn:
        if (tmpA == inChars[0])
        {
            state = u_keyIn;
        }
        else // (other / multiple keys)
        {
            state = locked;
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

    case u_keyIn:   break;
    
    case unlocked:  
        tmpB = 0x01;
        break;
    
    case l_keyIn:   break;

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
        tmpA =  PINA & 0x0F;
        tmpA7 = (PINA >> 7) & 0x01;

        Tick();

        PORTB = tmpB;
        PORTC = state;
    }
    
    return 1;
}
