/**
 * @file scheduler_s1.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.2
 * @date 2017-12-11; revision 2020_06_16
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */

#ifndef SCHEDULER_S1_H_
#define SCHEDULER_S1_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** @note you need to implement this file in your application (it can be empty if no need to change any settings) */
#include "rde_app_config.h"
#include "scheduler_s1_cfg_default.h"


typedef struct
{
    void (*run)(void);
    void (*task_exe)(void);
    void (*add_task)(void (*task)(void), uint32_t periode);
    void (*remove_task)(void (*task)(void));
    void (*new_singleShot)(void (*single_fptr)(void));

    uint8_t _task_active_F;
    uint8_t _active_task_ID;
    uint8_t _task_cnt;
    uint8_t _single_shot_task_cnt;
    uint8_t _fail_cnt;

} scheduler_t;

/**
 * @brief This is scheduler main structure that user use.
 */
extern scheduler_t Scheduler;


#ifdef __cplusplus
}
#endif

#endif /* SCHEDULER_S1_H_ */