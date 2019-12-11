/**
 * @file bubble_sort.h
 * @author Peter Medvese (peter.medvesek@gorenje.com)
 * @brief: TEST [OK]
 * @version 0.1
 * @date 2019-11-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef BUBBLE_SORT
#define BUBBLE_SORT

#include <stdint.h>
#include <stddef.h>


void bubble_sort (void* pBuffer, size_t nSize, size_t data_width, uint8_t (*pCompar)(const void*, const void*));


#endif /* BUBBLE_SORT */
