#ifndef _SERIAL_H
#define _SERIAL_H
/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Enables interface with PC via a serial port USART connection.
Can transmit EEPROM status strings and receive characters
('0','1','2','3') to signal what EEPROM section to check.
*/

typedef unsigned char byte;

/*
Initializes the USART for a serial connnection at 19,200 Baudrate
Serial connection is high-speed asynchronous.
*/
void SerialInit();

/*
Sends a byte of data through the serial port.
*/
void SendSerialChar(byte ch);

/*
Sends a string of character through the serial
port.
*/
void SendSerialString(const char *s);

/*
Receives a byte of data from the serial port.
*/
byte SerialReadChar();

/*
Returns whether the RCREG has something to read.
*/
byte SerialReadReady();

#endif