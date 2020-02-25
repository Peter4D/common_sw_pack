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


//#include "rde_app_config.h"
#include "scheduler_s1_cfg_default.h"


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