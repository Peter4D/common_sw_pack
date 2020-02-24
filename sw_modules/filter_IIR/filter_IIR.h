/**
 * @file filter_IIR.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief Infinite Impulse Response filter module. module utilise integer valuse and bit shift as 
 * division, to avoid "evil" float numbers. This is benificial on mcu-s that do not have floating point unit
 * @version 1.0
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
    IIR_value_t overSamp_acu;      // internal filter oversampled accumulator or value
    uint8_t     level;             // level or. power of filter like: 1 mean oversampled value is 2x actual
    /* possible extension, like flag when value is within stable threshold */
}IIR_desc_t;



/**
 * @brief Initialization of IIR filter channel
 * 
 * @param pDesc         : pointer to filter channel descriptor struct
 * @param level         : filter level or power 
 * @param init_value    : initil value from where filter will continoue
 */
void Filter_IIR_Init(IIR_desc_t* pDesc, uint8_t level, IIR_value_t init_value);


/**
 * @brief Put new value through filter
 * 
 * @param pDesc         :pointer to filter channel descriptor struct
 * @param newData       :new data that go into this filter channel
 * @return IIR_value_t  :return filtered value
 */
IIR_value_t Filter_IIR_Put(IIR_desc_t* pDesc, IIR_value_t newData);


/**
 * @brief Get back this channel filtered value 
 * 
 * @param pDesc         :pointer to filter channel descriptor struct
 * @return IIR_value_t  :filtered value out
 */
IIR_value_t Filter_IIR_Get(IIR_desc_t* pDesc);


/**
 * @brief return oversampled (super sampled), shifted left for filter level, value 
 * 
 * @param pDesc         :pointer to filter channel descriptor (cotrol block)struct
 * @return IIR_value_t  :filtered value out (oversampled)
 */
IIR_value_t Filter_IIR_over_samp_get(IIR_desc_t* pDesc);

/**
 * @brief return filter level value
 * 
 * @param pDesc         :pointer to filter channel descriptor (cotrol block)struct
 * @return IIR_value_t  :filter level 
 */
IIR_value_t Filter_IIR_level_get(IIR_desc_t* pDesc);


#endif /* FILTER_IIR_H */
