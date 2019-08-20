/*!
 * sw_timer.c
 *
 * @date    Created     24. 08. 2017 15:54:55
 * @date    revision    04. 04. 2019
 * @author: peter.medvesek
 */  

#include "sw_timer.h"

// this is added for use of assert facility
#include "debug_user.h"



//! method declaration
//! @ingroup methods
static void     pause_method            (sw_timer_t* pThis);
static bool     isElapsed_method        (sw_timer_t* pThis);
static void     attach_callBack_method  (sw_timer_t* pThis, f_ptr callback);
static void     set_method              (sw_timer_t* pThis, uint32_t set_value);
static void     reSet_method            (sw_timer_t* pThis, uint32_t set_value);
static void     clear_method            (sw_timer_t* pThis);
static uint32_t getTime_method          (sw_timer_t* pThis);

const struct _sw_timer_methods swTimer = {
    &set_method,
    &reSet_method,
    &clear_method,
    &getTime_method, 
    &pause_method, 
    &isElapsed_method, 
    &attach_callBack_method 
};

// module internal function
static uint8_t sw_tm_getNewSlot();

// Array of pointers to timers structs. It is limited. alternative is linked list 
#define SW_TM_INST_MAX	10
sw_timer_t* sw_timers[SW_TM_INST_MAX]; 

static uint8_t sw_tm_slot_id = 0;
uint8_t sw_tm_getNewSlot(sw_timer_t* pThis) {
	
	if (sw_tm_slot_id >= SW_TM_INST_MAX)
	{
        ASSERT_EMBED(0);
		return 1; // max number of counter reached
	} else {
		sw_timers[sw_tm_slot_id] = pThis;	
		// count number of software_timers
		++sw_tm_slot_id;
		return 0;
	}	
}


void _sw_timers_tick() {
	uint8_t i = 0;
    sw_timer_t *pTimer;

	for (i; i < sw_tm_slot_id; ++i) {
        pTimer = sw_timers[i]; 
		if (pTimer->_status == SWTM_RUNNING) {
			pTimer->_cnt++;
			
			if (pTimer->_cnt >= pTimer->_set_value && pTimer->_set_value != SWTM_CON_RUN) {
				pTimer->_status = SWTM_ELAPSED;
				pTimer->_cnt = 0;
				
				if (pTimer->_callback_fptr != NULL) {
					pTimer->_callback_fptr(); 
				}
			}
		} 		
	}
}

// constructor
void swTimer_init(sw_timer_t* pThis) {
	sw_tm_getNewSlot(pThis);
	
	pThis->_status = SWTM_STOP;
	pThis->_cnt = 0;
	pThis->_set_value = 0;
	pThis->_callback_fptr = NULL;
}


static void set_method(sw_timer_t* pThis, uint32_t set_value){
	pThis->_set_value = set_value;
	pThis->_status = SWTM_RUNNING;
}

static void reSet_method(sw_timer_t* pThis, uint32_t set_value) {
	pThis->_set_value = set_value;
	pThis->_status = SWTM_RUNNING;
	pThis->_cnt = 0;
}

static void clear_method(sw_timer_t* pThis) {
	pThis->_cnt = 0;
	pThis->_status = SWTM_STOP;
}

static uint32_t getTime_method(sw_timer_t* pThis) {
    return (pThis->_cnt);
}

static void pause_method(sw_timer_t* pThis) {
	pThis->_status = SWTM_PAUSE;
}

static bool isElapsed_method(sw_timer_t* pThis) {
	if (pThis->_status == SWTM_ELAPSED)
	{ 
		return true;
	} else {
		return false;
	}
}

static void attach_callBack_method(sw_timer_t* pThis, f_ptr callback) {
	pThis->_callback_fptr = callback;
}