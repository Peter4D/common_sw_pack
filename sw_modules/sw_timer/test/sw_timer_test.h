/**
 * @file sw_timer_test.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief because this module is hardware dependent, it is not complete
 * user need to complete/tailored to his project !
 * @version 0.1
 * @date 2019-12-16
 * 
 * @copyright Copyright (c) 2019 Gorenje d.o.o
 * 
 */
#ifndef SW_TIMER_TEST_H
#define SW_TIMER_TEST_H

#include "../sw_timer.h"

/**
 * @brief this perform test of sowtware timer module
 * @note: user need to call: swTimer_tick() by HW timer !!
 * 
 * @param ext_cb: user set through this callback what action will happen e.g. toogle led or pin and check
 * timming with osciloscope.
 */
void sw_timer_test_init(void (*ext_cb)(void));

#endif /* SW_TIMER_TEST_H */
