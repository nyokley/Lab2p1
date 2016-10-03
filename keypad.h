#ifndef KEYPAD_H    /* Guard against multiple inclusion */
#define KEYPAD_H

//TRIS output/input values
#define OUTPUT 0
#define INPUT 1

//ODC output values
#define CLOSED 0 //output is low
#define OPEN 1  //output is high

//rows, number indicates pin number
#define ROW_P2 LATDbits.LATD10
#define ROW_P4 LATEbits.LATE0
#define ROW_P6 LATEbits.LATE4
#define ROW_P7 LATEbits.LATE6
//columns, number indicates pin number
#define COL_P1 PORTCbits.RC3
#define COL_P3 PORTDbits.RD4
#define COL_P5 PORTEbits.RE2

//rows, number indicates pin number
#define TRIS_ROW_P2 TRISDbits.TRISD10
#define TRIS_ROW_P4 TRISEbits.TRISE0
#define TRIS_ROW_P6 TRISEbits.TRISE4
#define TRIS_ROW_P7 TRISEbits.TRISE6
//columns, number indicates pin number
#define TRIS_COL_P1 TRISCbits.TRISC3
#define TRIS_COL_P3 TRISDbits.TRISD4
#define TRIS_COL_P5 TRISEbits.TRISE2

#define ODC_ROW_P2 ODCDbits.ODCD10
#define ODC_ROW_P4 ODCEbits.ODCE0
#define ODC_ROW_P6 ODCEbits.ODCE4
#define ODC_ROW_P7 ODCEbits.ODCE6
//columns, number indicates pin number
#define CNPU_COL_P1 CNPUCbits.CNPUC3
#define CNPU_COL_P3 CNPUDbits.CNPUD4
#define CNPU_COL_P5 CNPUEbits.CNPUE2

void initKeypad();
int scanKeypad();

#endif /* _EXAMPLE_FILE_NAME_H */

