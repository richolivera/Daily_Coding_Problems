#ifndef INPUT_H
#define INPUT_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_STRING_LENGTH 255


int promptForInputString(char * prompt, char * inputStr
		, int maxInputSz);

int promptForInputInt(char * prompt, long int * inputInt);
#endif
