#ifndef _MAIN_H
#define _MAIN_H
/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Project: Interface with keypad, LCD (4-bit), and a serial port.
Read and write data to the onboard EEPROM.
*/

#include "main.h";

typedef unsigned char byte;

void CheckSerial();
void HandleKeyPress();
void ClearKey();
void ClearBuffer();
void EnterKey();
void HelpKey();
void SecondKey();
void UpKey();
void DownKey();
void NumKey(byte key);

#endif