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

#define SECOND              1000
#define MINUTE              60 * SECOND
#define HOUR                60 * MINUTE

typedef enum {
    SET_OFF = (uint8_t)0,
    SET_ON,

    SET_CNT
}on_off_e_t;

#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))

#define BIT_SET(var, bit, set_clear)                    \
    if( set_clear == 1) { var |= (1 << bit); }          \ 
    else if( set_clear == 0) { var &= ~(1 << bit); } 


#ifdef __cplusplus
}
#endif

#endif /* UTILITIES_H */
