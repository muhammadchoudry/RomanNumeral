/***********************************************************
File:			RomanCalculator.h
Description:	Class interface for RomanCalculator
				Designed to add/subtract roman numeral strings
By:				Muhammad Choudry
***********************************************************/

int validStringRomanNumeralCheck(char * input);
int validIntRomanNumeralCheck(int input);
int convertString2Int(char * input, int * output);
int convertInt2String(int input, char * output);	
int add(char * input1, char * input2, char * output);
int subtract(char * input1, char * input2, char * output);