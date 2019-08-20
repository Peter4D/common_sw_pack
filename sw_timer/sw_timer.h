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

typedef enum {SWTM_ELAPSED, SWTM_RUNNING, SWTM_PAUSE, SWTM_STOP, SWTM_MAX}sw_tmr_status_t;

typedef void (*f_ptr)(void);

typedef struct _sw_tmr{
	//private:
	uint32_t        _cnt;
	uint32_t        _set_value;
	sw_tmr_status_t _status;
	f_ptr           _callback_fptr;
}sw_timer_t;


struct _sw_timer_methods{
    //public:
	void     (*set)             (struct _sw_tmr*, uint32_t set_value);
	void     (*reSet)           (struct _sw_tmr*, uint32_t set_value);
	void     (*clear)           (struct _sw_tmr*);
    uint32_t (*getTime)         (struct _sw_tmr*);
	void     (*pause)           (struct _sw_tmr*);
	bool     (*isElapsed)       (struct _sw_tmr*);
	void     (*attach_callBack) (struct _sw_tmr*, f_ptr);
};

//this should be called periodically (like every milisecond) ... this drives software timers instances
void _sw_timers_tick(void);

//---------------------------------------------------------------------------------------------------------------------
// this is what user of this driver use!

// this is struct of methods(functions) of this softwareTimer driver
extern const struct _sw_timer_methods swTimer;
// initialization function set swTimer instance to default values and add pointer of it into array of swTimers
void swTimer_init(sw_timer_t* pThis);
//---------------------------------------------------------------------------------------------------------------------



#endif /* SW_TIMER_INCL_H_ */