/**
 * @file utilities.c
 * @author Medvese Peter (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2019-11-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "num_str_convert.h"

/**
 * @brief  helper function: do a second complement of a number
 * test: 2019_11_27 [OK] 
 * @param num 
 */
static void _2nd_complement(int32_t* num);


static void _2nd_complement(int32_t* num) {
	int32_t temp = 0;
	temp = (~(*num) + 1); 
	*num = temp;
}


uint8_t num2str(int32_t num_in, uint8_t *const pStr_out) {
	uint8_t i = 0;
	uint8_t i2 = 0;
	uint8_t num_cnt = 0;
	uint8_t sign_offset = 0;
	uint8_t temp_str[15];
	
	if (num_in == 0){
		pStr_out[0] = '0';
		pStr_out[1] = 0; // zero termination
        num_cnt = 0;
	} else {

		if (num_in < 0)
		{
			pStr_out[0] = '-';
			sign_offset = 1;
			_2nd_complement(&num_in);
		}
		for (i = 0; num_in > 0; i++)
		{
            /* @todo try to replace % operator (assumsion is that this is slow on 8bit) */
			temp_str[i] = (uint8_t)((num_in % 10) + '0'); // ascii shift for numbers 0 -> 48(dec)
			num_in = num_in / 10;
		}
		num_cnt = i;
		i += sign_offset;
		// add null termination at the end of string
		pStr_out[i] = 0;
		// revers array
		for (i2 = 0; i2 < num_cnt; i2++)
		{
			i--;
			pStr_out[i] = temp_str[i2];
		}
	}

    /* return string size */
	return (uint8_t)(num_cnt + sign_offset);
}


int32_t str2num(const uint8_t *const str) {
#define MUN_MAX_DIGIT_CNT       (30u)

	uint8_t i = 0;
    int8_t sign = 1;
	int32_t temp_num = 0;

    /* check if string is negative number */
    if(str[i] == '-') {
        sign = -1;
        ++i;
    } 

	for ( ; str[i] != 0; ++i)
	{
		if (i > MUN_MAX_DIGIT_CNT) {
            /* protection if string is not NULL terminated */
            temp_num = 0;
            break;
			// return 0; 
		}

		temp_num *= 10;
		if (str[i] >= '0' && str[i] <= '9')
		{
			temp_num += str[i] - '0';
		} else {
			/* this is not a number (NaN) */
            temp_num = 0;
            break;
			//return 0; 
		}
	}
	return (temp_num * sign);
}
