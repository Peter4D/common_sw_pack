/**
 * @file sw_timer.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2017-08-24 (created)
 * @date 2020-02-26 (revision)
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */
#ifndef SW_TIMER_INCL_H_
#define SW_TIMER_INCL_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/** @note you need to implement this file in your application (it can be empty if no need to change any settings) */
#include "rde_app_config.h"
#include "HOT_sw_timer_cfg_default.h"

#ifdef __cplusplus
extern "C" {
#endif

// if this value is set for set value timer will run continuously
#define SWTM_CON_RUN        (0u)
#define SW_TIMER_SET_MS(x)  (x / SW_TIMER_TICK_MS)


typedef enum 
{
    SWTM_STOP,
    SWTM_RUNNING,
    SWTM_PAUSE,
    SWTM_ELAPSED,
    SWTM_MAX
}sw_tmr_status_t;

typedef void (*pF_swTm)(void* p_arg);

typedef struct _sw_tmr{
    //private:
    uint8_t         _init_F;
    uint32_t        _cnt;
    uint32_t        _set_value;
    sw_tmr_status_t _status;
    pF_swTm         _callback_fptr;
    void* p_callback_arg;
}sw_timer_t;


struct _sw_timer_methods{
    //public:
    void     (*set)              (struct _sw_tmr*, uint32_t set_value);
    void     (*reSet)            (struct _sw_tmr*, uint32_t set_value);
    void     (*clear)            (struct _sw_tmr*);
    uint32_t (*getTime)          (struct _sw_tmr*);
    void     (*pause)            (struct _sw_tmr*);
    void     (*resume)           (struct _sw_tmr*);
    bool     (*isElapsed)        (struct _sw_tmr*);
    void     (*attach_callBack)  (struct _sw_tmr*, pF_swTm);
    void     (*set_callBack_arg) (struct _sw_tmr*, void* p_arg);
};

/**
 * @brief This drives software timers instances and should be called periodically.
 * This determine sw timer resolution (like every millisecond driven by hardware timer)
 */
void swTimer_tick(void);

//---------------------------------------------------------------------------------------------------------------------
// interface of software timer !

/* this is struct of methods(functions) of this softwareTimer module */
extern const struct _sw_timer_methods swTimer;

/**
 * @brief initialise swTimer instance to default values and add pointer of it into array of swTimers
 * 
 * @param pThis : pointer to software timer object.
 */
void swTimer_init(sw_timer_t* pThis);
//---------------------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif /* SW_TIMER_INCL_H_ */