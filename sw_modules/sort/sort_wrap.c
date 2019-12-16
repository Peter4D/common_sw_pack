#include "sort_wrap.h"
#include "median_filter.h"


uint8_t compare_int8(const void *a, const void *b)
{
    int8_t *cast_a = (int8_t *)a;
    int8_t *cast_b = (int8_t *)b;
    
    if(*cast_a > *cast_b){
        return 1;
    }else {
        return 0;
    }
}

uint8_t compare_int16(const void *a, const void *b)
{
    int16_t *cast_a = (int16_t *)a;
    int16_t *cast_b = (int16_t *)b;
    
    if(*cast_a > *cast_b){
        return 1;
    }else {
        return 0;
    }
}

