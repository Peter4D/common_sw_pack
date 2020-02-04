/**
 * @file filter_IIR.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 0.1
 * @date 2020-02-03
 * 
 * @copyright Copyright (c) 2020 Gorenje d.o.o
 * 
 */

#ifndef FILTER_IIR_H
#define FILTER_IIR_H

#include <stdint.h>

/**
 * @brief change this if you want to use this filter on different data types. But you can not use 
 * different types simultaneously. This is limitation of C language, that lacking templates, ...
 * or my imaginations :)
 */
typedef int32_t IIR_value_t; 


typedef struct _IIR_desc_t {
    uint32_t    overSamp_acu;      // internal filter oversampled accumulator or value
    uint8_t     level;             // level or. power of filter like: 1 mean oversampled value is 2x actual
    /* possible extension, like flag when value is within stable threshold */
}IIR_desc_t;


/**
 * @brief Initialization of IIR filter channel
 * 
 * @param pDesc pointer to filter channel descriptor struct
 */
void Filter_IIR_Init(IIR_desc_t* pDesc, IIR_value_t* acu, uint8_t level);

/**
 * @brief Put new value through filter
 * 
 * @param pDesc pointer to filter channel descriptor struct
 * @param newData new data that go into this filter channel
 */
void Filter_IIR_Put(IIR_desc_t* pDesc, IIR_value_t newData);

/**
 * @brief Get back this channle filtered value 
 * 
 * @param pDesc pointer to filter channel descriptor struct
 * @return IIR_value_t : filtered value out
 */
IIR_value_t Filter_IIR_Get(IIR_desc_t* pDesc);


#endif /* FILTER_IIR_H */
