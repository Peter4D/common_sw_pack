#include "digital_debounce.h"



#ifndef DEBOUCE_MSK
#define DEBOUCE_MSK         DEBOUCE_LEVEL_3
#endif


uint8_t digital_debounce(uint8_t* p_debouce, uint8_t new_value) {
    uint8_t return_val = 0;

    *p_debouce <<= 1;
    *p_debouce |= (new_value & 0x01);

    if((*p_debouce & DEBOUCE_MSK) == DEBOUCE_MSK) {
        return_val = 1;
    }else if((*p_debouce & DEBOUCE_MSK) == 0){
        return_val = 0;
    } 

    return return_val;
}