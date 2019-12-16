/**
 * @file num_str_convert.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2019-11-27
 * 
 * @copyright Copyright (c) 2019 Gorenje d.o.o
 * 
 */

#ifndef NUM_STR_CONVERT_INCL_H_
#define NUM_STR_CONVERT_INCL_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief convert interger number to c string (zero terminated)
 * test: 2019_11_27 [OK] 
 * @param num_in    : number taht will be conveted to c string (zero terminated)
 * @param pStr_out  : output string that contains string representation of input number
 * @return uint8_t  : return string lenght
 */
uint8_t num2str(int32_t num_in, uint8_t *const pStr_out);

/**
 * @brief convert c string (zero terminated) to interger number 
 * test: 2019_11_27 [OK] 
 * @param str       : input c string
 * @return int32_t  : converted number. 0 if NaN or is string is too long
 */
int32_t str2num(const uint8_t *const str); 

#endif /* NUM_STR_CONVERT_INCL_H_ */