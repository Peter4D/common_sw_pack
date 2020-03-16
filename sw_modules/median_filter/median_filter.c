
#include "median_filter.h"
#include <string.h>
/* dependencies */
#include "assert_hot_sw_pack"
#include "bubble_sort.h"

#undef _inline

#if defined(__GNUC__)
    #define _inline     __attribute__((always_inline))
#endif

#ifndef _inline
    #error provide inline keyword
    #define _inline
#endif

/**
 * @brief helper function of filter_median_put. put new value in right place and return median value
 * 
 * @param pDesc      : pointer to median stuct descriptor  
 * @param data      : new data that go into a filter 
 * @return median_value_t 
 */
static median_value_t get_median(median_desc_t *pDesc, median_value_t data);

/**
 * @brief helper function of get_median. find index of old value, that will be removed from filter, in window array
 * 
 * @param pDesc      : pointer to median stuct descriptor  
 * @return uint8_t   : position or inedx of the oldest value of current iteration.
 */
static uint8_t find_index(median_desc_t *pDesc);

/**
 * @brief compare function for bubble sort algorithm to sort median_data_t object 
 * 
 * @param a compare value 1
 * @param b compare value 2
 * @return uint8_t :1 if a > b | 0 if a < b
 */
uint8_t compare_median (const void *a, const void *b);

_inline void sort_median(void* pBuffer, size_t nSize) {
    bubble_sort(pBuffer, nSize, sizeof(median_data_t), compare_median);
}

uint8_t compare_median (const void *a, const void *b){
    median_data_t *cast_a = (median_data_t *)a;
    median_data_t *cast_b = (median_data_t *)b;

    if(cast_a->data > cast_b->data){
        return 1;
    }else {
        return 0;
    }
}

median_value_t filter_median_put(median_desc_t *pDesc, median_value_t newData) {
    median_data_t *pWindow = (median_data_t*)pDesc->pBuffer;
       
    median_value_t return_val = 0;

    /* stage_1: fill window */
    if(pDesc->window_fill_F == 0) {

        if(pDesc->newData_idx < pDesc->buff_size) {
            /* assign index to new data */
            pWindow[pDesc->newData_idx].idx = pDesc->newData_idx;
            pWindow[pDesc->newData_idx].data = newData;
            pDesc->newData_idx++;

            if(pDesc->newData_idx == pDesc->buff_size) {
                pDesc->window_fill_F = 1;
                pDesc->newData_idx = 0; 
                /* sort */
                sort_median(pWindow, pDesc->buff_size);
                return_val = pWindow[(pDesc->buff_size >> 1)].data;
            }else {
                /* till window is not fully filled up, value are just passthrough ! */
                return_val = pWindow[pDesc->newData_idx - 1].data;
            }
        }
    
    /* stage_2: put new value in window and retun median value */
    }else if(pDesc->window_fill_F == 1) {

        return_val = get_median(pDesc, newData);
        if(pDesc->newData_idx < (pDesc->buff_size - 1) )  {
            pDesc->newData_idx++;
        }else {
            pDesc->newData_idx = 0;
        }
    }
    return return_val;
}

/**
 * @brief helper function: put new data in median window and return median value
 * 
 * @param pDesc            : pointer to median stuct descriptor  
 * @param data             : new data that go into window
 * @return median_value_t  : returned median value
 */
median_value_t get_median(median_desc_t *pDesc, median_value_t data) {
    median_data_t *pWindow = (median_data_t*)pDesc->pBuffer;
    uint8_t old_val_idx = 0;

    ASSERT_HOT_SW_PACK(pDesc != NULL);

    /* index of the value in window that will be removed */
    old_val_idx = find_index(pDesc);

    /* put new  in a window */
    pWindow[old_val_idx].data = data;
    pWindow[old_val_idx].idx = pDesc->newData_idx;
    
    sort_median(pWindow, pDesc->buff_size);

    /* return value that is in a middle of a window (>> 1 equal to int divide by 2) */
    return pWindow[pDesc->buff_size >> 1].data;
}

/* find index in window array */
uint8_t find_index(median_desc_t *pDesc) {
    median_data_t *pWindow = (median_data_t*)pDesc->pBuffer;
    uint8_t i = 0;

    for(i = 0; i < pDesc->buff_size; ++i){
        if(pDesc->newData_idx == pWindow[i].idx) { 
            break;
        }
    }
    return i;
}

void filter_median_init(median_desc_t *pDesc, median_data_t *pData, size_t size) {
    ASSERT_HOT_SW_PACK(pData != NULL);
    ASSERT_HOT_SW_PACK(pDesc != NULL);
    
    pDesc->window_fill_F = 0;
    pDesc->newData_idx = 0;

    pDesc->pBuffer = pData;
    pDesc->buff_size = (uint8_t)size;
}

median_value_t filter_median_get(median_desc_t *pDesc) {
    return (pDesc->pBuffer[pDesc->buff_size >> 1].data);    
}