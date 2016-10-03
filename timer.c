/* 
 * File:   timer.c
 * Author: Alex Brooks
 *
 */

#include <xc.h>
#include <math.h>
#include "lcd.h"
#define TRUE 1
#define FALSE 0


static char newTime[9] = "00:00:00"; //needs to be static to be returned.

void startTimer1() {
    TMR1 = 0;
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = 3;
    PR1 = 39; // (10 Mhz *  1 ms))/256 equals approximately 39 for an interrupt every 39 sec.
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
    IPC1bits.T1IP = 7;
    T1CONbits.TON = 1;
}



void delayUs(int usec) {
    TMR2 = 0;
    PR2 = calculatePR(usec); // .05 Seconds
    T2CONbits.TCKPS = 3; //prescalar of 8.
    T2CONbits.TCS = 0;
    T2CONbits.TON = 1; // Start the timer  
    IPC2bits.T2IP = 7; //assign the interrupt priority. 
    while (IFS0bits.T2IF == 0); // Do nothing until the flag goes up
    IFS0bits.T2IF = 0; // Put the flag back down
    T2CONbits.TON = 0; // Turn off the timer    
}



int calculatePR(int usec) {
    int PRTIME = 0;
    PRTIME = floor((float) (usec * 10)) / 8 - 1; //prescalar of 8.

    return PRTIME;
}

char* stringifyTime(int currentTime) //parse the ms value and update.
{

    int msec_new = currentTime % 100;
    int sec_new = ((currentTime - msec_new) / 1000)%60;
    int minutes_new = (currentTime - msec_new - (100 * sec_new)) / 60000;
    
    newTime[0] = (((int) minutes_new) / 10) + 48;
    newTime[1] = (minutes_new % 10) + 48; 
    newTime[2] = ':';
    newTime[3] = (((int) sec_new) / 10) + 48;
    newTime[4] = (sec_new % 10) + 48;
    newTime[5] = ':';
    newTime[6] = (((int) msec_new) / 10) + 48;
    newTime[7] = (msec_new % 10) + 48;
    newTime[8] = '\0';
    return newTime;
}

char* clearTime(void) {
    int i = 7;
    for (; i >= 0; i--) {
        newTime[i] = (i == 2 || i == 5) ? ':' : '0'; //newTime[2] & newTime[5] -> :, everything else -> 0.
    }
    printStringLCD(newTime);
    return newTime;
}




/* *****************************************************************************
 End of File
 */
