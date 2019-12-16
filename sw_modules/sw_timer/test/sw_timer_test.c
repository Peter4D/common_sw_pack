#include "sw_timer_test.h"
#include "sw_timer.h"

/* optional include, depend on your project */
//#include "app_debug.h"

/* 1 second if timer resolution is 1ms */
#define CALL_PERIODE        (1000)

sw_timer_t test_timer;

void test_timer_cb(void);

void sw_timer_test(void) {
    /* init debug pin */
    //DEBUG_init();

    swTimer_init(&test_timer);
    swTimer.attach_callBack(&test_timer, test_timer_cb);
    /* start timer */
    swTimer.set(&test_timer, CALL_PERIODE);
}


void test_timer_cb(void) {
    /* user can chack timing on effected pin with osciloscope */
    //debug_pin_PE6_toggle();

    /* set nex cycle */
    swTimer.set(&test_timer, CALL_PERIODE);
}