#ifndef _KEYPAD_H
#define _KEYPAD_H
/*
SE4130 Spring 2019 - Lab 4
Names: Jacob Plapp, Tod Jones, Sarah Higgens

Enables interface with keypad (4-by-4 orientation) input
on a specified port. Provides software debouncing for button
presses and returns a character based on each of the 16
possible inputs as well as a null character for no press.
*/
#include <htc.h>

typedef unsigned char byte;

void KeypadInit();
byte KeyPressed();
byte GetKeyPress();
int GetColumn();
int GetRow();

#endif