/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Enables interface with 2x20 LCD screen. (4-bit support)
Initialize, clear, and update an attached LCD.
*/

#include <htc.h>;
#include "lcd.h"

typedef unsigned char byte;

#define _XTAL_FREQ 20000000 // 20MHz Processor

#define DATA_BUS 	PORTB
#define DATA_TRIS	TRISB

#define	REG_SEL		RC4
#define	CH_EN		RC5

#define SET_FUNC		0x02
#define CLR_DISP        0x01
#define DISP_ON_BLINK   0x0D
#define FUNC_SET_4X2    0x28
#define FUNC_SET_8X2    0x38
#define MOV_CURS_R0C0	0x80
#define	MOV_CURS_R1C0	0xC0

#define DATA_MASK_B30	0x0F
#define DATA_MASK_B41	0x1E
#define	DATA_MASK_B50	0x3F
#define	DISP_SIZE		0x14

void LCDInit(){	
	__delay_ms(50);
	DATA_TRIS = 0x00;
	REG_SEL = 0;
	LCDSendNibble(SET_FUNC);
	__delay_ms(6);
	LCDSendNibble(SET_FUNC);
	__delay_us(200);
	LCDSendInstruct(SET_FUNC);
	LCDSendInstruct(FUNC_SET_4X2);
	LCDSendInstruct(DISP_ON_BLINK);
	LCDSendInstruct(CLR_DISP);
	LCDSendInstruct(MOV_CURS_R0C0);
}

void LCDSendNibble(byte b){
	DATA_BUS = ((b << 1) & DATA_MASK_B41); //Send on RB4-RB1
	CH_EN = 1;
	__delay_us(5);
	CH_EN = 0;
	__delay_us(10);
}

void LCDSendByte(byte b){
	byte h = ((b >> 4) & DATA_MASK_B30);
	byte l = (b & DATA_MASK_B30);
	LCDSendNibble(h);
	__delay_us(50);
	LCDSendNibble(l);
	__delay_ms(1);
}

void LCDSendData(byte data){
	REG_SEL = 1;
	LCDSendByte(data);
}

void LCDSendInstruct(byte inst){
	REG_SEL = 0;
	LCDSendByte(inst);
}

void LCDWriteString(const char *s){
	while(*s) LCDSendData(*s++);
}

void LCDSetCursor(int r, byte addr){
	byte mem = (addr & DATA_MASK_B50);
	if(mem >= DISP_SIZE) 
		mem = (mem % DISP_SIZE);
	if(r == 1)
		LCDSendInstruct(MOV_CURS_R1C0|mem);
	else
		LCDSendInstruct(MOV_CURS_R0C0|mem);
}

void LCDClear(){
	LCDSendInstruct(CLR_DISP);
	LCDSendInstruct(MOV_CURS_R0C0);
}