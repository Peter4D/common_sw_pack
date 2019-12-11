#ifndef SORT_WRAP_H
#define SORT_WRAP_H

#include <stdint.h>
#include <stddef.h>
#include "bubble_sort.h"


uint8_t compare_int8   (const void *a, const void *b);
uint8_t compare_int16  (const void *a, const void *b);
uint8_t compare_median (const void *a, const void *b);


@inline void sort_int8(void* pBuffer, size_t nSize) {
    bubble_sort(pBuffer, nSize, sizeof(int8_t), compare_int8);
}

@inline void sort_int16(void* pBuffer, size_t nSize) {
    bubble_sort(pBuffer, nSize, sizeof(int16_t), compare_int16);
}

@inline void  sort_median(void* pBuffer, size_t nSize) {
    bubble_sort(pBuffer, nSize, sizeof(median_data_t), compare_median);
}


#endif /* SORT_WRAP_H */
