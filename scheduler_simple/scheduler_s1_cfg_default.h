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


#endif /* SCHEDULER_S1_CFG_DEFAULT_H */
