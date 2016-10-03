/* 
 * File:   timer.h
 * Author: Alex Brooks
 *
 */

#ifndef TIMER_H
#define	TIMER_H


void initTimer1();
void initTimer1_half();
void delayOneSecondTimer2();
void delayTenthSecondTimer2();
void delayUs(int usec);
char* stringifyTime(int currentTime);
void startTimer1();
#endif	/* TIMER_H */

