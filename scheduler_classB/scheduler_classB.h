/**
 * @file scheduler_classB.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.2
 * @date 2017-12-11; revision 2020_06_16
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */

#ifndef SCHEDULER_CLASSB_H_
#define SCHEDULER_CLASSB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/** @note you need to implement this file in your application (it can be empty if no need to change any settings) */
#include "rde_app_config.h"
#include "scheduler_s1_cfg_default.h"

#define SCHEDULER_TASK_ID_INVALID  0xFF

void scheduler_debug_msg_hook(const char* const prefix_msg, char* const debug_msg);

typedef struct
{
    void (*run)(void);
    void (*task_exe)(void);
    uint8_t (*add_task)(void (*task)(void), uint32_t periode);
    void (*remove_task)(uint8_t task_id);
    uint8_t (*get_active_task_id)(void);
    void (*new_singleShot)(void (*single_fptr)(void* p_arg), void* p_arg);

} scheduler_t;

/**
 * @brief This is scheduler main structure that user use.
 */
extern const scheduler_t Scheduler;

void Scheduler_init(void);


#ifdef __cplusplus
}
#endif

#endif /* SCHEDULER_CLASSB_H_ */