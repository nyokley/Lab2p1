/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _LCD_H    /* Guard against multiple inclusion */
#define _LCD_H

#define TRIS_RS  TRISCbits.TRISC4
#define TRIS_E   TRISCbits.TRISC2

#define LCD_RS  LATCbits.LATC4
#define LCD_E   LATCbits.LATC2

#define TRIS_D7 TRISEbits.TRISE1
#define TRIS_D6 TRISEbits.TRISE3
#define TRIS_D5 TRISEbits.TRISE5
#define TRIS_D4 TRISEbits.TRISE7

#define LCD_D7 LATEbits.LATE1
#define LCD_D6 LATEbits.LATE3
#define LCD_D5 LATEbits.LATE5
#define LCD_D4 LATEbits.LATE7

#define LCD_COMMAND 0
#define LCD_DATA 1

#define LOWER 1
#define UPPER 0

#define INPUT 1
#define OUTPUT 0

void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower);
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter);
void initLCD(void);
void clearLCD(void);
void moveCursorLCD(unsigned char x, unsigned char y);
void printCharLCD(char c);
void printStringLCD(const char* s);
void testLCD();
void printTimeStringLCD(int newTime);
void adjustedPrint(char* line1, char*line2);


#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
