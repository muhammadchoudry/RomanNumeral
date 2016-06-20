/***********************************************************
File:			TestAdd.c
Description:	Class interface for testing the program
				Designed to add/subtract roman numeral strings
By:				Muhammad Choudry
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <RomanCalculator.h>

int main(){
	printf("TestAdd\n");
	
	
	//Allocate memory for the string
	char *str = (char *) malloc(16*sizeof(char));	//Max Roman number has 15 characters + 1 for null character
	
	int input = 1;
	convertInt2String(input, str);
	
	//convertString2Int(str, &result);
	//printf("%i\n",result);
	
	
	//Free the memory for the string
	free(str);
	
	return 0;
}