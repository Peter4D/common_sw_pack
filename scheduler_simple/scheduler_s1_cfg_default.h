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
 * @brief _SW designate switch (1 | 0) if set to 1 then task will not have priority inhered by 
 * order in which was listed (called Scheduler.add())
 */
#ifndef SCHEDULER_NO_PRIORITY_BY_ORDER_SW
#define SCHEDULER_NO_PRIORITY_BY_ORDER_SW  0
#endif

#endif /* SCHEDULER_S1_CFG_DEFAULT_H */
