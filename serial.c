/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Enables interface with PC via a serial port USART connection.
Can transmit EEPROM status strings and receive characters
('0','1','2','3') to signal what EEPROM section to check.
*/

#include <htc.h>;
#include <stdio.h>;
#include "serial.h"

typedef unsigned char byte;

/*
Initializes the USART for a serial connnection at 19,200 Baudrate
Serial connection is high-speed asynchronous.
*/
void SerialInit(){
    TRISC = 0xC0;   // Tx/Rx on RC6/RC7
    RCSTA = 0x90;   // Serial Enabled & Continuous Non-Parity
    TXSTA = 0x24;   // Transmit Enabled
    ADCON1 = 0x06;  // All pins digital
    SPBRG = 64;     // High-Speed Async. Baud @ 19.2 kbps
}

/*
Sends a byte of data through the serial port.
*/
void SendSerialChar(byte ch){
    while(TXIF == 0); //wait until ready
    TXREG = ch;    
}

/*
Sends a string of character through the serial
port.
*/
void SendSerialString(const char *s){
    while(*s)
        SendSerialChar(*s++);
}

/*
Receives a byte of data from the serial port.
*/
byte SerialReadChar(){
	if(OERR){
		CREN = 0;
		CREN = 1;
	}	
    while(RCIF == 0);   //wait until received
    return RCREG;    
} 

/*
Returns whether the RCREG has something to read.
*/
byte SerialReadReady(){
    return RCIF;
}                   