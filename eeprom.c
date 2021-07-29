/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Enables read/write support to chip EEPROM.
*/
#include <htc.h>;
#include "eeprom.h";

typedef unsigned char byte;

void EE_Write(byte addr, byte value){
    eeprom_write(addr, value);
}

byte EE_Read(int index, int offset){
    byte addr = (index % 4) * 10;
    return eeprom_read(addr + offset);
}

void EE_Clear(){
	for (int i = 0; i < 4; i++){
	    EE_Write((i * 10), 0x00);	
	}
}

int EE_HasString(int index){
    byte addr = (index % 4) * 10;
    if(eeprom_read(addr) == 0xA8)
        return 1;
    return 0;
}

void EE_WriteString(int index, const char *s){
    byte addr = (index % 4) * 10;
    EE_Write(addr, 0xA8); 
    for (int i = 1; i < 10; i ++)
        EE_Write(addr + i, *s++);
}