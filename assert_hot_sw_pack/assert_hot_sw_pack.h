/**
 * @file assert_hot_sw_pack.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2019-12-16
 * 
 * @copyright Copyright (c) 2019 Gorenje d.o.o
 * 
 */

#ifndef _ASSERT_HOT_SW_PACK_
#define _ASSERT_HOT_SW_PACK_

#include <stdint.h>

/** @note you need to implement this file in your application (it can be empty if no need to change any settings) */
#include "rde_app_config.h"
#include "assert_hot_sw_pack_cfg_default.h"

#if (ASSERT_HOT_SW_PACK_DEBUG_EN == 0)
#define NDEBUG
#endif

extern void assert_hot_sw_pack_failed(uint8_t* file, uint32_t line);

#define ASSERT_HOT_SW_PACK(expr) ((expr) ? (void)0 : assert_hot_sw_pack_failed((uint8_t*)__FILE__, __LINE__))


#endif //_ASSERT_HOT_SW_PACK_