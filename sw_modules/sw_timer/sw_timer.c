/**
 * @file sw_timer.c
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2017-08-24 (created)
 * @date 2020-02-25 (modified)
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */
#include "sw_timer.h"

// this is added for use of assert facility
#include "../../assert_gorenje/assert_gorenje.h"



//! method declaration
//! @ingroup methods
static void     pause_method            (sw_timer_t* pThis);
static bool     isElapsed_method        (sw_timer_t* pThis);
static void     attach_callBack_method  (sw_timer_t* pThis, pF_swTm callback);
static void     set_method              (sw_timer_t* pThis, uint32_t set_value);
static void     reSet_method            (sw_timer_t* pThis, uint32_t set_value);
static void     flush_method            (sw_timer_t* pThis);
static uint32_t getTime_method          (sw_timer_t* pThis);


/**
 * @brief put instance(set pointer) of sw timer into array so that tick can function can update it
 * 
 * @param pThis     : pointer to instance that will be addad to array
 * @return uint8_t  : return 1 if max number ob timers is reached (error!) otherwise 0
 */
static uint8_t sw_tm_getNewSlot(sw_timer_t* pThis);

const struct _sw_timer_methods swTimer = {
    &set_method,
    &reSet_method,
    &flush_method,
    &getTime_method, 
    &pause_method, 
    &isElapsed_method, 
    &attach_callBack_method 
};


/* array of pointer to instances of software timers. alternative will be linked list
but if user o not use a lot of sw timers this is also adequate */
sw_timer_t *pSw_timers[SW_TM_INST_MAX]; 

/* track number of sw timer instances */
static uint8_t sw_tm_slot_id = 0;

static uint8_t sw_tm_getNewSlot(sw_timer_t* pThis) {
	
	if (sw_tm_slot_id >= SW_TM_INST_MAX)
	{
        ASSERT_HOT_SW_PACK(0);
		return 1; // max number of counter reached
	} else {
		pSw_timers[sw_tm_slot_id] = pThis;	
		// count number of software_timers
		++sw_tm_slot_id;
		return 0;
	}	
}


void swTimer_tick() {
	uint8_t i = 0;
    sw_timer_t *pTimer;

	for (i; i < sw_tm_slot_id; ++i) {
        pTimer = pSw_timers[i]; 
		if (pTimer->_status == SWTM_RUNNING) {
			pTimer->_cnt += SW_TIMER_TICK_MS;
			
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

/* constructor */
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

static void flush_method(sw_timer_t* pThis) {
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

static void attach_callBack_method(sw_timer_t* pThis, pF_swTm callback) {
	pThis->_callback_fptr = callback;
}
