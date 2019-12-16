/**
 * @file popCount_test.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 0.1
 * @date 2019-12-12
 * 
 * @copyright Copyright (c) Gorenje d.o.o 2019
 * 
 */

#ifndef POPCOUNT_TEST_H
#define POPCOUNT_TEST_H

#include <stdint.h>

/**
 * @brief test routine for popCount function: return number relay information 
 * about which test fail in test array.
 * 
 * @return uint_fast8_t : > 1 - test [fail] | 0 - test [pass]
 */
uint_fast8_t popCount_test(void);

#endif /* POPCOUNT_TEST_H */
