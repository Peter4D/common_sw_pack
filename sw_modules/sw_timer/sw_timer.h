/*!
 * sw_timer.h
 *
 * @date    Created     24. 08. 2017 15:54:55
 * @date    revision    22.10.2018
 * @author: peter.medvesek
 */ 

#ifndef SW_TIMER_INCL_H_
#define SW_TIMER_INCL_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// if this value is set for set value timer will run continuously
#define SWTM_CON_RUN        (0u)

typedef enum 
{
    SWTM_STOP,
    SWTM_RUNNING,
    SWTM_PAUSE,
    SWTM_ELAPSED,
    SWTM_MAX
}sw_tmr_status_t;

typedef void (*pF_swTm)(void);

typedef struct _sw_tmr{
	//private:
	uint32_t        _cnt;
	uint32_t        _set_value;
	sw_tmr_status_t _status;
	pF_swTm         _callback_fptr;
}sw_timer_t;


struct _sw_timer_methods{
	//public:
    /**
     * @brief :set timer to set_value and start it
     */
	void     (*set)             (struct _sw_tmr*, uint32_t set_value);

    /**
     * @brief timer is set to set_value and timer counter is set to: 0
     */
	void     (*reSet)           (struct _sw_tmr*, uint32_t set_value);

    /**
     * @brief stop timer and set timer counter to: 0 
     */
	void     (*clear)           (struct _sw_tmr*);

    /**
     * @brief return current value of timer counter
     */
    uint32_t (*getTime)         (struct _sw_tmr*);

    /**
     * @brief pause timer (timer do not get updated)
     */
	void     (*pause)           (struct _sw_tmr*);

    /**
     * @brief return true if timer reach setted value 
     */
	bool     (*isElapsed)       (struct _sw_tmr*);

    /**
     * @brief attach callback that get called when timer reach setted value (elapsed)
     */
	void     (*attach_callBack) (struct _sw_tmr*, pF_swTm);
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

#endif /* SW_TIMER_INCL_H_ */