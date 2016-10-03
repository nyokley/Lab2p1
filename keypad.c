#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "keypad.h"




void initKeypad(){
    
    ANSELD = 0x0000;
    ANSELE = 0x0000;
    
    // Rows set as outputs
    TRIS_ROW_P2 = 0;
    TRIS_ROW_P4 = 0;
    TRIS_ROW_P6 = 0;
    TRIS_ROW_P7 = 0;

    
    // Columns set as inputs
    TRIS_COL_P1 = 1;
    TRIS_COL_P3 = 1;
    TRIS_COL_P5 = 1;
    
    // Enabling ODC mode for output pins
    ODC_ROW_P2 = 1;
    ODC_ROW_P4 = 1;
    ODC_ROW_P6 = 1;
    ODC_ROW_P7 = 1;
    
    // Input pins need pull-ups
    CNPU_COL_P1 = 1;
    CNPU_COL_P3 = 1;
    CNPU_COL_P5 = 1;
    
    // Now enable CN for each input pin
    CNCONCbits.ON = 1; //Enable overall CN Interrupt CNCONx
    CNCONDbits.ON = 1;
    CNCONEbits.ON = 1;
    CNENEbits.CNIEE2 = 1;//Enable pin CN CNENx
    CNENCbits.CNIEC3 = 1;//Enable pin CN CNENx
    CNENDbits.CNIED4 = 1;//Enable pin CN CNENx
    IFS1bits.CNCIF = 0;//Put down the flag //IFSx
    IFS1bits.CNDIF = 0;
    IFS1bits.CNEIF = 0;
    IPC8bits.CNIP = 7;//Set an interrupt priority //IPCx
    IEC1bits.CNCIE = 1;//Enable interrupt for D pins
    IEC1bits.CNDIE = 1;
    IEC1bits.CNEIE = 1;
    
    // "Close" the ODC
    ROW_P2 = CLOSED;
    ROW_P4 = CLOSED;
    ROW_P6 = CLOSED;
    ROW_P7 = CLOSED;
}

int scanKeypad(){
    int key = -1;
    
    //Disable CN Interrupt
    IEC1bits.CNEIE = 0;
    IEC1bits.CNCIE = 0;
    IEC1bits.CNDIE = 0;
    
    // turn on only one row
    ROW_P2 = CLOSED;
    ROW_P7 = OPEN;
    ROW_P6 = OPEN;
    ROW_P4 = OPEN;
    
    delayUs(5000);
    if(COL_P3 == 0) key += '1';
    else if(COL_P1 == 0) key += '2';
    else if(COL_P5 == 0) key += '3';
    
    //repeat scan
    ROW_P2 = OPEN;
    ROW_P7 = CLOSED;
    ROW_P6 = OPEN;
    ROW_P4 = OPEN;
    
    delayUs(5000);
    if(COL_P3 == 0) key += '4';
    else if(COL_P1 == 0) key += '5';
    else if(COL_P5 == 0) key += '6';
    
    //repeat scan
    ROW_P2 = OPEN;
    ROW_P7 = OPEN;
    ROW_P6 = CLOSED;
    ROW_P4 = OPEN;
    
    delayUs(5000);
    if(COL_P3 == 0) key += '7';
    else if(COL_P1 == 0) key += '8';
    else if(COL_P5 == 0) key += '9';
    
    //repeat scan
    ROW_P2 = OPEN;
    ROW_P7 = OPEN;
    ROW_P6 = OPEN;
    ROW_P4 = CLOSED;
    
    delayUs(5000);
    if(COL_P3 == 0) key += '*';
    else if(COL_P1 == 0) key += '0';
    else if(COL_P5 == 0) key += '#';
    
    // Return to keypad on
    ROW_P2 = CLOSED;
    ROW_P7 = CLOSED;
    ROW_P6 = CLOSED;
    ROW_P4 = CLOSED;
    
    // turn on the CN Interrupt
    IEC1bits.CNCIE = 1;
    IEC1bits.CNDIE = 1;
    IEC1bits.CNEIE = 1;
    
    if(key <= '9' && key > 0) {
        return key + 1; //key is initially -1
    }
    //if key > 9, two buttons were pressed
    else {
        return -1;
    }
 }
