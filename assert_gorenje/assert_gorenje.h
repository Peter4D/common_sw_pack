/**
 * @file assert_gorenje.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 1.0
 * @date 2019-12-16
 * 
 * @copyright Copyright (c) 2019 Gorenje d.o.o
 * 
 */

#ifndef _ASSERT_GORENJE_
#define _ASSERT_GORENJE_

#include <stdint.h>

/* @note: this is here fo safety if user is not aware of assert it is better to be disabled
comment out this if you want to use assert feature !! */
#define NDEBUG


extern void assert_hot_sw_pack_failed(uint8_t* file, uint32_t line);

//#undef assert
#define ASSERT_HOT_SW_PACK(expr) ((expr) ? (void)0 : assert_hot_sw_pack_failed((uint8_t*)__FILE__, __LINE__))


#endif //_ASSERT_GORENJE_