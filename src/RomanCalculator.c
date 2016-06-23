/***********************************************************
File:			RomanCalculator.h
Description:	Implementation of the RomanCalculator Class
				Designed to add/subtract roman numeral strings
By:				Muhammad Choudry
***********************************************************/

#include <stdio.h>
#include <string.h>

//Convert a roman numeral character to integer format
//The return value returns if the input was successfully converted or not
int convertChar2Int(char input, int * value){
	switch (input) {
		case 'I': *value= 1; break;
		case 'V': *value = 5; break;
		case 'X': *value = 10; break;
		case 'L': *value = 50; break;
		case 'C': *value = 100; break;
		case 'D': *value = 500; break;
		case 'M': *value = 1000; break;
		case 'i': *value= 1; break;
		case 'v': *value = 5; break;
		case 'x': *value = 10; break;
		case 'l': *value = 50; break;
		case 'c': *value = 100; break;
		case 'd': *value = 500; break;
		case 'm': *value = 1000; break;
		default: return 0;
	}
	return 1;	
}

//Check to see if integer can be used as a roman numeral
int validIntRomanNumeralCheck(int input){
	if (input < 0 || input > 3999){
		return 0;	
	} else {
		return 1;	
	}
}

//Check to see if the string is a valid roman numeral
int validStringRomanNumeralCheck(char * input){
	
	int length = strlen(input);
	
	//Check to see if the range is within length
	if (length == 0 || length > 15){
		return 0;	
	}
	
	int value = -1;
	int next_value = -1;
	int last_value = -1;
	int last_last_value = -1;
	
	int count = 0;
	int pos;
	for (pos = length-1; pos >=0; pos--){
		
		int result1 = 1;
		int result2 = 1;
		//Get the current character value
		if (pos == length-1){
			result1 = convertChar2Int(input[pos],&value);
		} else {
			value = next_value;
		}
		//Get the next character value
		if (pos != 0){
			result2 = convertChar2Int(input[pos-1],&next_value);
		}
		
		//Invalid character
		if (result1==0 || result2==0){
			return 0;	
		}
		
		//Keep track of repeated characters
		if (last_value == value){
			count++;	
		} else {
			count = 0;	
		}
		
		//Characters can only repeat 1 time
		if ( value==5 || value==50 || value==500 ){
			if (count >= 1){
				return 0;	
			}
		//Characters can only repeat 3 times
		} else if (value == 1 || value == 10 || value == 100 || value == 1000){
			if (count >= 3){
				return 0;
			}
		} 
		
		if (last_value >= 0){
			//Subtracting a value
			if (value < last_value){
				
				//Can only subtract one of I,X,C,M
				if (!(value == 1 || value == 10 || value == 100 || value == 1000)){
					return 0;
				}
				
				//Subtracted value must be either 1/5 or 1/10 of the last value
				if (!(  ((5*value)==last_value) || ((10*value)==last_value)  )){
					return 0;
				}
				
				//Must be either first numeral or 10 times smaller than next 
				if (!(  (pos == 0) || ( next_value*10 >= value) )){
					return 0;	
				}
				
				//We're in the middle then next value must be >= last value
				if (pos > 0 && pos < length-1){
					if (!(next_value >= last_value)){
						return 0;	
					}
				}
				
				//First part of compound numeral must be bigger than numeral after
				if (last_last_value >= -0){
					if (!( last_last_value < value )){
						return 0;	
					}
				}
				
			}
		}
		
		if (last_value == -1){
			last_value = value;
		} else {
			last_last_value = last_value;
			last_value = value;
		}
	}
	
	return 1;
	
}

//Convert a string roman number to integer format
//The return value returns if the input was successfully converted or not
int convertString2Int(char * input, int * output){
	//Check to see if int is with in range
	if (validStringRomanNumeralCheck(input) == 0){
		return 0;
	}
	
	*output = 0;
	typedef enum {add,subtract} modes;
	modes mode = add;
	
	int length = strlen(input);
	int pos; 
	
	//Do the conversion
	int last_value = 0;
	for (pos = length-1; pos >= 0; pos--){
		int value = 0;
		
		int result = convertChar2Int(input[pos],&value);
		if (result == 0){
			return 0;	
		}
		
		//Subtract if value to the left is less than the value to the right
		if (pos + 1 < length){
			if (value < last_value){
				mode = subtract;
			} else {
				mode = add;
			}
		}
					
		if (mode == add){
			*output = *output + value;
		}else{
			*output = *output - value;
		}
		
		last_value = value;
	}
	
	//Return status
	return validIntRomanNumeralCheck(*output);
}

//Convert an integer to a roman number format
//The return value returns if the input was successfully converted or not
int convertInt2String(int input, char * output){
	//Check to see if int is with in range
	if (validIntRomanNumeralCheck(input) == 0){
		return 0;
	}
	
	strcpy(output,"");
	
	//Some data structions to help us do the conversion
	int num_possibilities = 13;
	const char *options[num_possibilities];
	options[0] = "M";
	options[1] = "CM";
	options[2] = "D";
	options[3] = "CD";
	options[4] = "C";
	options[5] = "XC";
	options[6] = "L";
	options[7] = "XL";
	options[8] = "X";
	options[9] = "IX";
	options[10] = "V";
	options[11] = "IV";
	options[12] = "I";
	int boundaries[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
	
	//Convert the string
	while (input != 0){
		int boundary = 0;
		
		int i = 0;
		for (i = 0; i < num_possibilities; i++){
			if (input >= boundaries[i]){
				boundary = i;
				break;
			}
		}	
		input = input - boundaries[boundary];	
		strcat(output,options[boundary]);
	}
	
	//Return status
	return 1;
}

//Add two input roman numerals together 
//The return value returns if calculation was completed successfully
int add(char * input1, char * input2, char * output){
	int num_input1;
	int num_input2;
	int num_output;
	if (convertString2Int(input1, &num_input1)==0){return 0;}
	if (convertString2Int(input2, &num_input2)==0){return 0;}
	num_output = num_input1 + num_input2;
	if (validIntRomanNumeralCheck(num_output) == 0){return 0;}
	convertInt2String(num_output, output);
	return 1;
}

//Subtract one roman numeral from another;
//The return value returns if calculation was completed successfully
int subtract(char * input1, char * input2, char * output){
	int num_input1;
	int num_input2;
	int num_output;
	if (convertString2Int(input1, &num_input1)==0){return 0;}
	if (convertString2Int(input2, &num_input2)==0){return 0;}
	num_output = num_input1 - num_input2;
	printf("num_output:%i\n",num_output);
	if (validIntRomanNumeralCheck(num_output) == 0){return 0;}
	convertInt2String(num_output, output);
	return 1;
}
