#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
#include "keypad.h"


// ******************************************************************************************* //

typedef enum stateEnum { //all states are for debouncing; states handle LEDs.
    waitPress,
    readKey,
    waitRelease,
    writeKey,
    debouncePress,
    debounceRelease,     
    clearKey
} stateType;

volatile stateType state = waitPress;
 char key;
int main(void)
{
    
    int keyCount = 0;
    
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    
    initLCD();
    initKeypad();
    
    while(1) {
        switch(state) {
            case waitPress:
                break;
            case readKey:
                key = scanKeypad();
                //delayUs(5000);
                state = waitRelease;
                break;
            case waitRelease:
                break;
            /*case clearKey:         //marks key as invalid if multiple keys are pressed 
                key = -1;
                state = waitRelease;
                break;*/
             
            case debounceRelease:
                delayUs(5000);
                state = writeKey;
                break;        
            case writeKey:
                if(key != -1) {
                    printCharLCD(key);
                    ++keyCount;
                    if(keyCount == 16) {
                        moveCursorLCD(0,2);
                    }
                    if(keyCount == 32) {
                        moveCursorLCD(0,1);
                        keyCount = 0;
                    }   
                }
                state = waitPress;
                break;
        }
    }
}
                
            
             


/*void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(void) {
    IFS0bits.T1IF = 0; //lower the flag 
    if(state == run)
    {
        currentTime += 1; //add 1 ms if we are running, otherwise ignore!
    }
}*/

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    IFS1bits.CNCIF = 0;
    IFS1bits.CNDIF = 0;
    IFS1bits.CNEIF = 0;
    
    int x, y, z;
    x = PORTC; // clearing the mismatch condition
    y = PORTD;
    z = PORTE;
    
    if(state == waitPress) {
        state = readKey;
    }
    else if (state == waitRelease && COL_P3 && COL_P1 && COL_P5 ) {
        state = debounceRelease;
    }
    /*else if (state == waitRelease){
        state = clearKey;
    }*/
    
    
    
} 