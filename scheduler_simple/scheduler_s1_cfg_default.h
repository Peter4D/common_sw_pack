/**
 * @file scheduler_s1_cfg_default.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-25
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */
#ifndef SCHEDULER_S1_CFG_DEFAULT_H
#define SCHEDULER_S1_CFG_DEFAULT_H

/**
 * @brief Scheduler run period in milliseconds. This must be set to correct value in order for task to execute in 
 * correct timer periode. If Scheduler.run() is called every 10 ms, set this parameter to 10 !
 * @note This is default config file this parameter must be set in rde_app_cfg.h file !!
 */
#ifndef SCHEDULER_TICK_MS
#define SCHEDULER_TICK_MS      1
#endif

/**
 * @brief maximum number of task that can be set 
 */
#ifndef SCHEDULER_TASK_MAX
#define SCHEDULER_TASK_MAX    15
#endif

/**
 * @brief maximum number of quick single shot calls (task) that can be in queue
 */
#ifndef SCHEDULER_SINGLE_MAX
#define SCHEDULER_SINGLE_MAX  10
#endif


/**
 * @brief This set number of time that scheduler detect busy state... taks is still executing
 * e.g. if set to 5 and scheduler run every 1 ms this means that one task is stalling for 5 ms 
 */
#ifndef SCHEDULER_TIME_OUT
#define SCHEDULER_TIME_OUT  5
#endif

#endif /* SCHEDULER_S1_CFG_DEFAULT_H */
