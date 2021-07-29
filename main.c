/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Project: Interface with keypad, LCD (4-bit), and a serial port.
Read and write data to the onboard EEPROM.
*/

#include <htc.h>;
#include <stdio.h>;
#include <string.h>;

#include "main.h";
#include "lcd.h";
#include "serial.h";
#include "keypad.h";
#include "eeprom.h";


// Osc = HS, Watchdog Off, all other features disabled
__CONFIG(0x3F3A);

#define _XTAL_FREQ 20000000 // 20MHz Processor
#define TRUE  1
#define FALSE 0
#define TO_CHAR 0x30
#define LCD_MAX 0x09

typedef unsigned char byte;

static int _EEI = 0;				// EEPROM index counter - 0-4
static char scanner[LCD_MAX];	// Input buffer
static int sc_index = 0;			// Input buffer index

/*
Program Main - Lab 4
*/
void main(){
    SerialInit();   // Enable Serial Connection
    KeypadInit();	// Initialize Keypad
	LCDInit();		// Initialize LCD
    do{
        if(SerialReadReady())
            CheckSerial();
        if(KeyPressed()){
            HandleKeyPress();
    	}
    }while(TRUE);
    return;
}

/*
Checks the serial port connection for data and handles it
appropriately.
*/
void CheckSerial(){
    int valid = TRUE;
    byte input = SerialReadChar();
    switch(input){
        case '0': _EEI = 0; break;
        case '1': _EEI = 1; break;
        case '2': _EEI = 2; break;
        case '3': _EEI = 3; break;
        default: valid = FALSE; break;
    } 
    if (valid == TRUE)
        HelpKey();
}

/*
Handles a key press from a Keypad and performs the
associate action.
*/
void HandleKeyPress(){
    byte key = GetKeyPress();
	switch(key){
    	case '0': NumKey(key); break;
    	case '1': NumKey(key); break;
    	case '2': NumKey(key); break;
    	case '3': NumKey(key); break;
    	case '4': NumKey(key); break;
    	case '5': NumKey(key); break;
    	case '6': NumKey(key); break;
    	case '7': NumKey(key); break;
    	case '8': NumKey(key); break;
    	case '9': NumKey(key); break;
		case 'E': EnterKey(); break;
		case 'C': ClearKey(); break;
		case 'H': HelpKey(); break;
		case 'U': UpKey(); break;
		case 'D': DownKey(); break;
		case 'S': SecondKey(); break;
		default: break;
	}
	__delay_ms(250);	//Software Debounce
}        

/*
Used for writing serial output to UART I/O in Debugger
*/
void putch(byte data){
	while(!TXIF);
	TXREG = data;
}

/*
Handles Clear Key press by clearing LCD and the input buffer.
*/
void ClearKey(){
    LCDClear();
    ClearBuffer();
}  

/*
Clears input buffer by resetting index.
*/
void ClearBuffer(){
    sc_index = 0;
}    

/*
Pads input buffer to the right with whitespace and writes it
to the EEPROM. Clears the LCD and displays the updated EEPROM
saved string in the second row.
*/
void EnterKey(){
	if(sc_index == 0) return;		// Don't write blank string
    if(sc_index < LCD_MAX - 1){	
        for(int i = sc_index; i < LCD_MAX; i++)
            scanner[i] = ' ';		// Pad remaining spaces
    }
    EE_WriteString(_EEI, scanner);
    LCDClear();
    LCDSetCursor(1,0x00);			// Set LCD cursor to 2nd row
    LCDSendData(_EEI + TO_CHAR);	// Send _EEI index as char to LCD
	LCDSendData(':');				// Send ':' to LCD
	LCDWriteString(scanner);		// Write buffer to LCD.
	LCDSetCursor(0, 0x00);			// Set LCD cursor to 1st row
	ClearBuffer();
}      

/*
Clears LCD and displays the current EEPROM index and its
associated value on the LCD's second row and to the serial
output.
*/
void HelpKey(){
	LCDClear();
	LCDSetCursor(1,0x00);
	LCDSendData(_EEI + TO_CHAR);
	LCDSendData(':');
	if(EE_HasString(_EEI)){
    	byte temp = 0x00;
    	SendSerialChar(_EEI + TO_CHAR);
		SendSerialChar(':');
    	for (int i = 1; i < 10; i++){
        	temp = EE_Read(_EEI,i);
        	LCDSendData(temp);
        	SendSerialChar(temp);
        }
            SendSerialString("\r\n");
	} else {
		LCDWriteString("No String");
		SendSerialChar(_EEI + TO_CHAR);
		SendSerialChar(':');
		SendSerialString("No String\r\n");
	}
	LCDSetCursor(0, 0x00);
    ClearBuffer();
}  

/*
Clears EEPROM contents and the LCD. Writes a status message
to the serial output.
*/
void SecondKey(){
    EE_Clear();
    LCDClear();
    ClearBuffer();
    SendSerialString("EEPROM Cleared.\r\n");
}   

/*
Increments the EEPROM index and displays the new EEPROM
location on the LCD and serial output.
*/
void UpKey(){
    _EEI = (_EEI + 1) % 4;
	HelpKey();
} 

/*
Decrements the EEPROM index and displays the new EEPROM
location on the LCD and serial output.
*/
void DownKey(){
    _EEI = (_EEI - 1) % 4;
	HelpKey();
}    

/*
Writes a character to the input buffer and to the LCD's 
first row. Ensures that no more than LCD_MAX_INDEX characters 
can be typed to the LCD or buffer.
*/
void NumKey(byte key){
    scanner[sc_index] = key;
    if(sc_index < LCD_MAX - 1){
        sc_index++;
        LCDSendData(key);
    } else {
        LCDSendData(key); 
        LCDSetCursor(0,LCD_MAX - 1);        
    }    
}