/**
 * @file median_filter.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief
 * Meadian filter. Object orintated style. Median window size is provided by user 
 * it use data window that is sorted by bubble sort and every new value is
 * put into right place, so the window remain sorted. other value are shifted (memcpy)
 * in a way that remove the oldest value in window
 * @version 1.0
 * @date (created) 2019-11-20 (revision) 2019-11-26
 * 
 * @copyright Copyright (c) Gorenje d.o.o. 2019
 * 
 */

#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <stdint.h>
#include <stdlib.h>

/**
 * @brief change this if you want to use this filter on different data types. But you can not use 
 * different types simultaneously. This is limitation of C language, that lacking templates, ...
 * or my imaginations :)
 */
typedef uint32_t median_value_t; 

//=================================================================================================
// data types 
typedef struct _median_data_t {
    uint8_t        idx;  // this index remember order of data that is put into window (because of sorting)
    median_value_t data; // data type on which filter will be performed
}median_data_t;

typedef struct _median_buff_t {
    median_data_t   *pBuffer;       // pointer to median window data type 
    uint8_t         buff_size;      // size of data window
    uint8_t         window_fill_F;  // flag: if window is fully populated (at start)
    uint8_t         newData_idx;    // index to track order of data that go into a window
}median_desc_t;

//=================================================================================================

/**
 * @brief initialize median filter data channel 
 * 
 * @param pDesc : descriptor of filter data channel (can be used on multiple channels )
 * @param pData : pointer to data container (buffer) for median window
 * @param size  : size of data container (buffer)
 */
void filter_median_init(median_desc_t *pDesc, median_data_t *pData, size_t size);

/**
 * @brief return median value 
 * 
 * @param pDesc           : descriptor of filter data channel (can be used on multiple channels )
 * @param newData         : new data that is put into median filter window
 * @return median_value_t : filtered median value 
 */
median_value_t filter_median_get(median_desc_t *pDesc, median_value_t newData);


#endif /* MEDIAN_FILTER_H */
