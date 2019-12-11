
#include <string.h>

/* dependencies */
#include "assert_stm8_gorenje.h"
#include "median_filter.h"
#include "sort_wrap.h"

/**
 * @brief helper function of filter_median_get. put new value in right place and return median value
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


median_value_t filter_median_get(median_desc_t *pDesc, median_value_t newData) {
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

/* this version of function do not work ... @todo investigate why
fail appear in test_data[11]; error in memmove source and dest. are offset by one,
but this is not reflected in code!
*/
// median_value_t get_median(median_desc_t *pDesc, median_value_t data) {
//     median_data_t *pWindow = (median_data_t*)pDesc->pBuffer;

//     uint8_t i = 0;
//     uint8_t old_val_idx = 0;
//     uint8_t num_of_byte2move = 0;
//     uint8_t nConst = 0;

//     assert(pDesc != NULL);

//     /* index of the value in window that will be removed */
//     old_val_idx = find_index(pDesc);

//     /* find index in sorted window where new value will be put in, so that window will remain sorted */
//     for(i = 0; i < pDesc->buff_size; ++i) {
//         if(data <= pWindow[i].data || i == pDesc->buff_size - 1) {
//             /* find place  */
//             break;
//         }
//     }

//     //num_of_byte2move = (int8_t)((old_val_idx - i) * sizeof(median_data_t));
    
//     if(old_val_idx > i){
//         nConst = 0;
//         num_of_byte2move = (uint8_t)((old_val_idx - i) * sizeof(median_data_t));
//         memmove(&pWindow[i + 1], &pWindow[i], num_of_byte2move);
//     }else if (old_val_idx < i) {
//         nConst = 1;
//         //num_of_byte2move = (int8_t)((i - old_val_idx - nConst) * sizeof(median_data_t));
//         num_of_byte2move = (i - old_val_idx) - nConst;
//         num_of_byte2move *= sizeof(median_data_t);
//         memmove(&pWindow[(i - 1) - nConst], &pWindow[(i) - nConst], num_of_byte2move );
//     }else if(old_val_idx == i){
//         nConst = 0
//     }

//     /* put new data in to a free up spot in a window */
//     pWindow[i - nConst].data = data;
//     pWindow[i - nConst].idx = pDesc->newData_idx;

//     /* return value that is in a middle of a window (>> 1 equal to int divide by 2) */
//     return pWindow[pDesc->buff_size >> 1].data;
// }

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

    assert(pDesc != NULL);

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
    assert(pData != NULL);
    assert(pDesc != NULL);
    
    pDesc->window_fill_F = 0;
    pDesc->newData_idx = 0;

    pDesc->pBuffer = pData;
    pDesc->buff_size = (uint8_t)size;
}