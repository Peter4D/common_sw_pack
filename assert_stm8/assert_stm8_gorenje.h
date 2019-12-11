
#ifndef _ASSERT_STM8_GORENJE_
#define _ASSERT_STM8_GORENJE_

#include <stdint.h>

/* @note this is not essential part of this module. Should be removed because app_debug is clearly application
specific part ! */
#include "app_debug.h"

extern void assert_failed(uint8_t* file, uint32_t line);

#define assert(expr) ((expr) ? (void)0 : assert_failed((uint8_t*)__FILE__, __LINE__))


#endif //_ASSERT_STM8_GORENJE_