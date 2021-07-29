#ifndef _LCD_H
#define _LCD_H
/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Enables interface with 2x20 LCD screen. (4-bit support)
Initialize, clear, and update an attached LCD.
*/

typedef unsigned char byte;

void LCDInit();
void LCDSendNibble(byte b);
void LCDSendByte(byte b);
void LCDSendData(byte data);
void LCDSendInstruct(byte inst);
void LCDWriteString(const char *s);
void LCDSetCursor(int r, byte addr);
void LCDClear();

#endif
