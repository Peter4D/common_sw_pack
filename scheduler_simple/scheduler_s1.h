/*
 * scheduler_2.c
 *
 * Created: 11. 12. 2017; revision: 11.12.2019
 *  Author: peter.medvesek
 */


#ifndef SCHEDULER_S1_H_
#define SCHEDULER_S1_H_

#include <stdint.h>

typedef struct {
	void (*task_run) (void);
	uint32_t tm_periode;
	uint32_t tm_elapsed;
}task_t;

typedef struct {
	void (*run)				(void);
	void (*task_exe)		(void);
	void (*add_task)		(void (*task)(void), uint32_t periode);
	void (*new_singleShot)	(void(*single_fptr)(void));

	uint8_t _task_active_F; 
	uint8_t _single_active_F;
	uint8_t _active_task_ID;
	
}scheduler_t;

extern scheduler_t* scheduler;

/* this is redundant: only to use (->) syntax instead of (.)*/
scheduler_t* sceduler_Init(void);


#endif /* SCHEDULER_S1_H_ */