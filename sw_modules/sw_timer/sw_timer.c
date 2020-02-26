/**
 * @file sw_timer.c
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2017-08-24 (created)
 * @date 2020-02-26 (revision)
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */
#include "sw_timer.h"

// this is added for use of assert facility
#include "../../assert_gorenje/assert_gorenje.h"

//=================================================================================================
//! @ingroup methods_declaration

/**
 * @brief pause timer (timer do not get updated)
 * 
 * @param pThis : Pointer to instance of software timer object(control struct).
 */
static void pause(sw_timer_t* pThis);

/**
 * @brief : Return 1 if timer reaches setted value.
 * 
 * @param pThis     : Pointer to instance of software timer object(control struct).
 * @return uint8_t  : 1 if timer is elapsed | 0 if it still counting.
 */
static uint8_t isElapsed(sw_timer_t* pThis);

/**
 * @brief : Attach callback that get called when timer reach setted value (elapsed)
 * 
 * @param pThis     : Pointer to instance of software timer object(control struct).
 * @param callback  : Callback function that is called when timer elapsed.
 */
static void attach_callBack(sw_timer_t* pThis, pF_swTm callback);

/**
 * @brief : Set timer to set_value and start it
 * 
 * @param pThis     : Pointer to instance of software timer object(control struct).
 * @param set_value : Timer value in milliseconds 
 */
static void set(sw_timer_t* pThis, uint32_t set_value);

/**
 * @brief   Timer is set to set_value and timer counter is set to: 0
 * 
 * @param pThis     : Pointer to instance of software timer object(control struct).
 * @param set_value : Timer value in milliseconds 
 */
static void reSet(sw_timer_t* pThis, uint32_t set_value);

/**
 * @brief   stop timer and set timer counter to: 0 
 * 
 * @param pThis : Pointer to instance of software timer object(control struct).
 */
static void clear(sw_timer_t* pThis);

/**
 * @brief return current value of timer counter
 * 
 * @param pThis     : Pointer to instance of software timer object(control struct).
 * @return uint32_t : curent value of timer counter in milliseconds
 */
static uint32_t getTime(sw_timer_t* pThis);

//methods_declaration_end
//=================================================================================================

/**
 * @brief Put instance(set pointer) of sw timer into array so that tick function can update it.
 * 
 * @param pThis     : Pointer to instance that will be addad to array
 * @return uint8_t  : Return 1 if max number ob timers is reached (error!) otherwise 0
 */
static uint8_t sw_tm_getNewSlot(sw_timer_t* pThis);

const struct _sw_timer_methods swTimer = {
    &set,
    &reSet,
    &clear,
    &getTime, 
    &pause, 
    &isElapsed, 
    &attach_callBack 
};


/* Array of pointers to instances of software timers. alternative will be linked list
but if user do not use a lot of sw timers this is also adequate */
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


void swTimer_tick(void) {
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


static void set(sw_timer_t* pThis, uint32_t set_value){
    pThis->_set_value = set_value;
    pThis->_status = SWTM_RUNNING;
}

static void reSet(sw_timer_t* pThis, uint32_t set_value) {
    pThis->_set_value = set_value;
    pThis->_status = SWTM_RUNNING;
    pThis->_cnt = 0;
}

static void clear(sw_timer_t* pThis) {
    pThis->_cnt = 0;
    pThis->_status = SWTM_STOP;
}

static uint32_t getTime(sw_timer_t* pThis) {
    return (pThis->_cnt);
}

static void pause(sw_timer_t* pThis) {
    pThis->_status = SWTM_PAUSE;
}

static uint8_t isElapsed(sw_timer_t* pThis) {
    if (pThis->_status == SWTM_ELAPSED) { 
        return 1;
    } else {
        return 0;
    }
}

static void attach_callBack(sw_timer_t* pThis, pF_swTm callback) {
    pThis->_callback_fptr = callback;
}