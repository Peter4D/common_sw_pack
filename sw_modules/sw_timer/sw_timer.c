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
#include "assert_hot_sw_pack.h"

//=================================================================================================
//! @ingroup methods_declaration

/**
 * @brief pause timer (timer do not get updated)
 * 
 * @param pThis : Pointer to instance of software timer object(control struct).
 */
static void pause(sw_timer_t* pThis);

/**
 * @brief set paused timer back to active state
 * 
 * @param pThis : Pointer to instance of software timer object(control struct).
 */
static void resume(sw_timer_t* pThis);

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
 * @brief Set callback arguments pointer
 * 
 * @param pThis     : Pointer to an instance of software timer object(control struct).
 * @param p_arg     : pointer to argument that will be pass into callback function  
 *                  when will be called.
 */
static void set_callBack_arg(sw_timer_t* pThis, void* p_arg);

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
    .set = &set,
    .reSet = &reSet,
    .clear = &clear,
    .getTime = &getTime, 
    .pause = &pause, 
    .resume = &resume,
    .isElapsed = &isElapsed, 
    .attach_callBack = &attach_callBack,
    .set_callBack_arg = &set_callBack_arg 
};


static struct _m_sw_timer_t
{
    /* Array of pointers to instances of software timers. alternative will be linked list
    but if user do not use a lot of sw timers this is also adequate */
    sw_timer_t* p_timers_slot[SW_TM_INST_MAX];
    uint8_t slot_id;
}m = {
    .slot_id = 0
};


static uint8_t sw_tm_getNewSlot(sw_timer_t* pThis) {

    if (m.slot_id >= SW_TM_INST_MAX)
    {
        ASSERT_HOT_SW_PACK(0);
        return 1; // max number of counter reached
    } else {
        m.p_timers_slot[m.slot_id] = pThis;
        // count number of software_timers
        ++m.slot_id;
        return 0;
    }
}


void swTimer_tick(void) {
    sw_timer_t *pTimer = NULL;

    for (uint8_t i = 0; i < m.slot_id; ++i) {
        pTimer = m.p_timers_slot[i]; 
        if (pTimer->_status == SWTM_RUNNING) {
            pTimer->_cnt += SW_TIMER_TICK_MS;
            
            if (pTimer->_cnt >= pTimer->_set_value && pTimer->_set_value != SWTM_CON_RUN) {
                pTimer->_status = SWTM_ELAPSED;

                if (pTimer->_callback_fptr != NULL) {
                    pTimer->_callback_fptr(pTimer->p_callback_arg); 
                }
                /**  @todo this at the moment is needed. in callback user can check what was last set time,
                 * but if used in polling mode (.isElapsed), this info is not available because of this 
                 * line of code. ... refactor is this feature is needed: 
                 */
                pTimer->_cnt = 0; 
            }
        }
    }
}

/* constructor */
void swTimer_init(sw_timer_t* pThis) {
    if(pThis->_init_F == 0) {
        sw_tm_getNewSlot(pThis);

        pThis->_status = SWTM_STOP;
        pThis->_cnt = 0;
        pThis->_set_value = 0;
        pThis->_callback_fptr = NULL;
        pThis->p_callback_arg = NULL;

        pThis->_init_F = 1;
    }
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

static void resume(sw_timer_t* pThis){
    pThis->_status = SWTM_RUNNING;
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

static void set_callBack_arg(sw_timer_t* pThis, void* p_arg) {
    pThis->p_callback_arg = p_arg;
}