/**
 * @file scheduler_s1.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2017-12-11; revision 2020_02_24
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */

#ifndef SCHEDULER_S1_H_
#define SCHEDULER_S1_H_

#include <stdint.h>

/**
 * @brief Scheduler run period in milliseconds. This must be set to correct value in order for task to execute in 
 * correct timer periode. If Scheduler.run() is called every 10 ms, set this parameter to 10 !
 */
#define SCHEDULER_TICK_MS      1


typedef struct
{
    void (*run)(void);
    void (*task_exe)(void);
    void (*add_task)(void (*task)(void), uint32_t periode);
    void (*new_singleShot)(void (*single_fptr)(void));

    uint8_t _task_active_F;
    uint8_t _single_active_F;
    uint8_t _active_task_ID;
    uint8_t _task_cnt;
    uint8_t _single_shot_task_cnt;

} scheduler_t;

/**
 * @brief This is scheduler main structure that user use.
 */
extern scheduler_t Scheduler;


#endif /* SCHEDULER_S1_H_ */