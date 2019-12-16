/**
 * @file num_str_convert_test.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2019-12-16
 * 
 * @copyright Copyright (c) 2019 Gorenje d.o.o
 * 
 */

#ifndef NUM_STR_CONVERT_TEST_H
#define NUM_STR_CONVERT_TEST_H

#include "num_str_convert.h"

/**
 * @brief performed number of test for str2num function. To see what test are done look
 * into implementation.
 * @return uint8_t : return 0 if all test pass, otherwise return fail test id that is binary encoded 
 * as bit field. 0x04 mean that test id 2 is fail
 */
uint8_t test_str2num(void);

/**
 * @brief performed number of test for num2str function. To see what test are done look
 * into implementation.
 * @return uint8_t : return 0 if all test pass, otherwise return fail test id that is binary encoded 
 * as bit field. 0x04 mean that test id 2 is fail
 */
uint8_t test_num2str(void);

#endif /* NUM_STR_CONVERT_TEST_H */
