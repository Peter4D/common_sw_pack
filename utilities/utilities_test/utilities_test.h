#ifndef UTILITIES_TEST_H
#define UTILITIES_TEST_H

#include "utilities.h"

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

#endif /* UTILITIES_TEST_H */
