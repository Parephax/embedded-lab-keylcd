/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Enables interface with keypad (4-by-4 orientation) input
on a specified port. Provides software debouncing for button
presses and returns a character based on each of the 16
possible inputs as well as a null character for no press.
*/

#include <htc.h>;
#include "keypad.h"

#define KPPORT PORTD        // Keypad Port
#define KPTRIS TRISD        // Port TRIS
#define KPMASK 0xF0         // Read/Write
#define _XTAL_FREQ 20000000 // 20MHz Processor

typedef unsigned char byte;

void KeypadInit(){
    KPTRIS = 0xF0;  // Read(High)/Write(Low)
}    

byte KeyPressed(){
    KPPORT = KPMASK;
    if(KPPORT < KPMASK){        
        return 0x01;
    }    
    return 0x00;
}    

byte GetKeyPress(){
    byte col = (0x01 << GetColumn());
    byte row = (0x01 << GetRow());
    byte key = col | row;
    switch(key){
        case 0x11: key = '1'; break;
        case 0x12: key = '4'; break;
        case 0x14: key = '7'; break;
        case 0x18: key = 'C'; break;
        case 0x21: key = '2'; break;
        case 0x22: key = '5'; break;
        case 0x24: key = '8'; break;
        case 0x28: key = '0'; break;
        case 0x41: key = '3'; break;
        case 0x42: key = '6'; break;
        case 0x44: key = '9'; break;
        case 0x48: key = 'H'; break;
        case 0x81: key = 'U'; break;
        case 0x82: key = 'D'; break;
        case 0x84: key = 'S'; break;
        case 0x88: key = 'E'; break;
        default: key = 'x';
    }    
    return key;
}  

int GetColumn(){
    KPPORT = KPMASK;
    byte x = ((KPPORT >> 4) & 0x0F);
    for(byte i = 0; i < 4; i++){
        if((x & 0x01) == 0)
            return i + 4;
        x = x >> 1;
    }
    return ('x');    
}

int GetRow(){
    byte x = 0x01;
    for(byte i = 0; i < 4; i++){
        KPPORT = ~(x);
        if(KPPORT < KPMASK)
            return i;
        x = x << 1;
    }
    return (0x01);    
}          