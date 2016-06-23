/***********************************************************
File:			TestAdd.c
Description:	Class interface for testing the program
				Designed to add/subtract roman numeral strings
By:				Muhammad Choudry
***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "RomanCalculator.h"

//Test conversion across entire range of valid numbers
//Input is a file range_test.csv that has the conversions
START_TEST(test_range)
{
	int int_input;
	char* str_input = malloc(16 * sizeof(char));
	int int_output;
	char *str_output = (char *) malloc(16*sizeof(char));
	
	FILE* stream = fopen("range_test.csv", "r");
    char line[1024];
    while (fgets(line, 1024, stream)){
		
		//Parse inputs from file (number,string)
		char *token = strtok(line,",");
		int counter=0;
		while( token != NULL ) 	
		{	
			if (counter == 0){
				sscanf (token, "%i", &int_input);
			} else if (counter == 1){
				sscanf (token, "%s", str_input);
			} else {
				break;	
			}
			token = strtok(NULL,",");
			counter++; 
		}	  
	
		//Perform the conversion test
		int result1 = convertInt2String(int_input, str_output);
		int result2 = convertString2Int(str_input, &int_output);
		
		ck_assert_str_eq(str_output, str_input);
		ck_assert_int_eq(int_output, int_input);
		ck_assert_int_eq(result1, 1);
		ck_assert_int_eq(result2, 1);

	}
	fclose(stream);
	free(str_input);
	free(str_output);
		
}
END_TEST

//Test a successful addition 
START_TEST(test_add_successful)
{
	//"MMDCXXXVIII"=2638;
	//"DCXLI"=641;
	//"MMMCCLXXIX"=3279=2638+641
	char *str = (char *) malloc(16*sizeof(char));
	int result = add("MMDCXXXVIII","DCXLI",str);
	ck_assert_str_eq(str, "MMMCCLXXIX");
	ck_assert_int_eq(result, 1);
	free(str);
}
END_TEST

//Test a successful subtraction 
START_TEST(test_subtract_successful)
{
	//"MMDCXXXVIII"=2638;
	//"DCXLI"=641;
	//"MCMXCVII"=1997=2638-641
	char *str = (char *) malloc(16*sizeof(char));
	int result = subtract("MMDCXXXVIII","DCXLI",str);
	ck_assert_int_eq(result, 1);
	free(str);
}
END_TEST

//Test an unsuccessful addition (overflow)
START_TEST(test_add_unsuccessful)
{
	//"MMDCXXXVIII"=2638;
	//"MMDCXXXVIII"=2638;
	//Result should be overflow
	char *str = (char *) malloc(16*sizeof(char));
	int result = add("MMDCXXXVIII","MMDCXXXVIII",str);
	ck_assert_int_eq(result, 0);
	free(str);
}
END_TEST

//Test an unsuccessful subtraction (underflow)
START_TEST(test_subtract_unsuccessful)
{
	//"DCXLI"=641;
	//"MMDCXXXVIII"=2638;
	//Result should be underflow
	char *str = (char *) malloc(16*sizeof(char));
	int result = subtract("DCXLI","MMDCXXXVIII",str);
	ck_assert_int_eq(result, 0);
	free(str);
}
END_TEST
	
//Test empty string
START_TEST(test_empty)
{
	//""
	//"MMDCXXXVIII"=2638;
	//Result should be underflow
	char *str = (char *) malloc(16*sizeof(char));
	int result1 = subtract("","MMDCXXXVIII",str);
	int result2 = subtract("MMDCXXXVIII","",str);
	int result3 = subtract("","",str);
	ck_assert_int_eq(result1, 0);
	ck_assert_int_eq(result2, 0);
	ck_assert_int_eq(result3, 0);
	free(str);
}
END_TEST
	
//Test long string
START_TEST(test_long)
{
	//""
	//"MMDCXXXVIII"=2638;
	//Result should be underflow
	char *str = (char *) malloc(16*sizeof(char));
	int result1 = subtract("MMMDCCCLXXXVIII","I",str);
	int result2 = subtract("MMMDCCCLXXXVIIIX","I",str);
	ck_assert_int_eq(result1, 1);
	ck_assert_int_eq(result2, 0);
	free(str);
}
END_TEST
	
//Test invalid strings
START_TEST(test_invalid_string)
{
	int int_output;
	int result;
	
	//To many I's
	result = convertString2Int("VIIII", &int_output);
	ck_assert_int_eq(result, 0);
	
	//Too many I's
	result= convertString2Int("IIIIV", &int_output);
	ck_assert_int_eq(result, 0);
	
	//Invalid character
	result = convertString2Int("VIU", &int_output);
	ck_assert_int_eq(result, 0);
	
	//Invalid numeral
	result = convertString2Int("MXMX", &int_output);
	ck_assert_int_eq(result, 0);
	
	//Invalid numeral
	result = convertString2Int("CDXIIV", &int_output);
	ck_assert_int_eq(result, 0);
	
	//Invalid numeral
	result = convertString2Int("IXI", &int_output);
	ck_assert_int_eq(result, 0);
	
}
END_TEST
	
//Case sensitivity
START_TEST(test_case_sensitivity)
{
	//"MMDCXXXVIII"=2638;
	//"DCXLI"=641;
	//"MMMCCLXXIX"=3279=2638+641
	char *str = (char *) malloc(16*sizeof(char));
	int result = add("mmdcxxxviii","dcxli",str);
	ck_assert_str_eq(str, "MMMCCLXXIX");
	ck_assert_int_eq(result, 1);
	free(str);
}
END_TEST

Suite * test_suite(void)
{	
	Suite *s;
	TCase *tc_range;
	TCase *tc_addsuccess;
	TCase *tc_subtractsuccess;
	TCase *tc_addunsuccess;
	TCase *tc_subtractunsuccess;
	TCase *tc_empty;
	TCase *tc_long;
	TCase *tc_invalid_string;
	TCase *tc_case_sensitivity;

	s = suite_create("RomanCalculator");

	tc_range			= tcase_create("RangeTest");
	tc_addsuccess 		= tcase_create("AddSuccessful");
	tc_subtractsuccess 	= tcase_create("SubtractSuccessful");
	tc_addunsuccess 	= tcase_create("AddUnsuccessful");
	tc_subtractunsuccess= tcase_create("SubtractUnsuccessful");
	tc_empty 			= tcase_create("EmptyInput");
	tc_long				= tcase_create("LongInput");
	tc_invalid_string	= tcase_create("InvalidString");
	tc_case_sensitivity	= tcase_create("Case Sensitivity");

	tcase_add_test(tc_range, test_range);
	tcase_add_test(tc_addsuccess, test_add_successful);
	tcase_add_test(tc_subtractsuccess, test_subtract_successful);
	tcase_add_test(tc_addunsuccess, test_add_unsuccessful);
	tcase_add_test(tc_subtractunsuccess, test_subtract_unsuccessful);
	tcase_add_test(tc_empty, test_empty);
	tcase_add_test(tc_long, test_long);
	tcase_add_test(tc_invalid_string, test_invalid_string);
	tcase_add_test(tc_case_sensitivity, test_case_sensitivity);
	
	suite_add_tcase(s, tc_range);
	suite_add_tcase(s, tc_addsuccess);
	suite_add_tcase(s, tc_subtractsuccess);
	suite_add_tcase(s, tc_addunsuccess);
	suite_add_tcase(s, tc_subtractunsuccess);
	suite_add_tcase(s, tc_empty);
	suite_add_tcase(s, tc_long);
	suite_add_tcase(s, tc_invalid_string);
	suite_add_tcase(s, tc_case_sensitivity);

	return s;
}

int main(void){
	
	int number_failed;
	Suite *s;
	SRunner *sr;
	
	s = test_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
	
}