/***********************************************************
File:			Readme.txt
Description:	Details on how to use RomanCalculator
By:				Muhammad Choudry
***********************************************************/

Requirements (Tested on this platform):
 - Ubuntu 14.04 64bit
 - GNU Make 3.81
 - GCC 4.8.4
 - C Check test framework 0.10

Organization of files:
 - src: 
 	- Source code for RomanCalculator.c 
 - include
 	- header file for RomanCalculator.h
 - test: 
 	- Source code for testsuite.c
 - bin:
 	- Directory where testsuite executable gets compiled to
 	- range_test.csv (read in my testsuite for testing purposes)
 - lib:
 	- where static lib gets built to

To run the test suite
	make all
	cd bin
	./testsuite
	
The test suite runs the following checks:
 - Conversion from int to string and string to int for full range of roman numerals
 - Checks valid cases of addition/subtraction
 - Checks invalid cases of addition/subtraction (overflow/underflow)
 - Empty string 
 - long strings
 - Incorrect roman numerals
 	- with invalid characters
	- invalid arrangement of characters
 - case sensitivity check


A note on design philosphy of RomanCalculator API
 - The function signature of RomanCalculator require both input,output variables to be passed to the function
 	- User is responsible for allocating appropriate amount of memory (atleast 16 characters worth) for string output
 - The return value indicates weather or not the function successfully completed the task (0=fail,1=success)
 	- It is up to the user of the library to determine how to handle the error for their specific applications
 	
A note on builds:
 - libromancalculator.a: release build that does not print out any error messages, but will indicate error with return value
 - libromanalculator_debug.a: a debug build which prints out error messages
