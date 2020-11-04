/**
 * @file utilities.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 0.1
 * @date 2020-10-19
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SET_OFF = 0,
    SET_ON
}on_off_e_t;

#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))


#ifdef __cplusplus
}
#endif

#endif /* UTILITIES_H */
