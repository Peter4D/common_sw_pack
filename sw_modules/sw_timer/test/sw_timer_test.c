/**
 * @file sw_timer_test.c
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2019-12-16 (created)
 * @date 2020-02-26 (revision)
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */
#include "sw_timer_test.h"


/* 1 second */
#define CALL_PERIODE        (1000)

/**
 * @brief instance of software timer object (control struct instance)
 */
static sw_timer_t test_timer;

static void (*sw_timer_test_extern_callback)(void) = NULL;

/**
 * @brief timer instance callback function 
 */
void test_timer_cb(void);

void sw_timer_test_init(void (*ext_cb)(void)) {
    /* user can set project specific function that for example manipulate digital output and check
    timing on effected pin with osciloscope */
    sw_timer_test_extern_callback = ext_cb;

    swTimer_init(&test_timer);
    swTimer.attach_callBack(&test_timer, test_timer_cb);
    /* start timer */
    swTimer.set(&test_timer, CALL_PERIODE);
}

void test_timer_cb(void) {

    if(sw_timer_test_extern_callback != NULL) {
        sw_timer_test_extern_callback();
    }
    /* set nex cycle */
    swTimer.set(&test_timer, CALL_PERIODE);
}