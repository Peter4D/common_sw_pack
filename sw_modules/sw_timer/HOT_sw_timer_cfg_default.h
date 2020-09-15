/**
 * @file HOT_sw_timer_cfg_default.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief This file contain default sttings for this sw_timer module.  if some setting need to be altered 
 * user need to provide file: app_global_config.h and #define USE_GLOBAL_APP_CFG  !
 * @version 1.0
 * @date 2020-02-25
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */
#ifndef SW_TIMER_CFG_DEFAULT_H
#define SW_TIMER_CFG_DEFAULT_H

/** @note @todo not in use */
#ifndef SW_TIMER_ENABLED
#define SW_TIMER_ENABLED    1
#endif


/**
 * @brief This set software timer tick resolution in milliseconds. This need to be changed if timer is driver at 
 * different rate. e.g. 10ms,  then this parameter  need to be set to 10. 
 * @note This is a default value if need to be changed, do this in rde_app_config.h (global application settings file)
 */
#ifndef SW_TIMER_TICK_MS
#define SW_TIMER_TICK_MS    1
#endif

/**
 * @brief Because this is implemented as fixed size array of pointers to software timers control structure(block)
 * this parameter set size of this array and therefor maximum number of posible software timers instances.
 * @note This is a default value if need to be changed, do this in rde_app_config.h (global application settings file)
 */
#ifndef SW_TM_INST_MAX
#define SW_TM_INST_MAX      15
#endif

#endif /* SW_TIMER_CFG_DEFAULT_H */
