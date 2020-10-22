/**
 * @file digital_debounce.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 0.1
 * @date 2020-10-22
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */
#ifndef DIGITAL_DEBOUNCE_H
#define DIGITAL_DEBOUNCE_H

#include <stdint.h>
/** @note you need to implement this file in your application (it can be empty if no need to change any settings) */
#include "rde_app_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DEBOUCE_LEVEL_0 = 0x01,
    DEBOUCE_LEVEL_1 = 0x03,
    DEBOUCE_LEVEL_2 = 0x07,
    DEBOUCE_LEVEL_3 = 0x0F,
    DEBOUCE_LEVEL_4 = 0x1F,
    DEBOUCE_LEVEL_5 = 0x3F,
    DEBOUCE_LEVEL_6 = 0x7F,
    DEBOUCE_LEVEL_7 = 0xFF
}debouce_level_t;

uint8_t digital_debounce(uint8_t* p_debouce, uint8_t new_value);

#ifdef __cplusplus
}
#endif

#endif /* DIGITAL_DEBOUNCE_H */
