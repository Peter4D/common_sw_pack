/**
 * @file median_filter_cfg_default.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-26
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */
#ifndef MEDIAN_FILTER_CFG_DEFAULT_H
#define MEDIAN_FILTER_CFG_DEFAULT_H

#include <stdint.h>

/**
 * @brief change this if you want to use this filter on different data types. But you can not use 
 * different types simultaneously. This is limitation of C language, that lacking templates, ...
 * or my imaginations :)
 */
#ifndef median_value_t
typedef int32_t median_value_t; 
#endif

#endif /* MEDIAN_FILTER_CFG_DEFAULT_H */
