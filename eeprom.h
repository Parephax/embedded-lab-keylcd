#ifndef _EERPOM_H
#define _EEPROM_H
/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Enables read/write support to chip EEPROM.
*/

typedef unsigned char byte;

void EE_Write(byte addr, byte value);
byte EE_Read(int index, int offset);
void EE_Clear();
int EE_HasString(int index);
void EE_WriteString(int index, const char *s);

#endif