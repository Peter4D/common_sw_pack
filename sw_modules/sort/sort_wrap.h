#ifndef SORT_WRAP_H
#define SORT_WRAP_H

#include <stdint.h>
#include <stddef.h>
#include "bubble_sort.h"


#if defined(__GNUC__) 
#define _inline          inline
#endif

#ifndef _inline
    #error provide inline keyword
    #define _inline
#endif


uint8_t compare_int8   (const void *a, const void *b);
uint8_t compare_int16  (const void *a, const void *b);


_inline void sort_int8(void* pBuffer, size_t nSize) {
    bubble_sort(pBuffer, nSize, sizeof(int8_t), compare_int8);
}

_inline void sort_int16(void* pBuffer, size_t nSize) {
    bubble_sort(pBuffer, nSize, sizeof(int16_t), compare_int16);
}


#endif /* SORT_WRAP_H */
