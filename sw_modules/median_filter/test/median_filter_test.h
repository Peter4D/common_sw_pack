/**
 * @file median_filter_test.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief usecase:
 * ----------------------------------------
 * volatile uint8_t median_test_res = 255;
 * median_test_res = test_median_filter();
 * if(median_test_res) { test_fail }
 * ----------------------------------------
 * @version 0.1
 * @date 2019-11-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MEDIAN_FILTER_TEST_H
#define MEDIAN_FILTER_TEST_H

#include <stdint.h>

uint8_t test_median_filter(void);


#endif /* MEDIAN_FILTER_TEST_H */
