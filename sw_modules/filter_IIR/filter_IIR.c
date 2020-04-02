#include "filter_IIR.h"


void Filter_IIR_Init(IIR_desc_t* pDesc, uint8_t level, IIR_value_t init_value) {
    pDesc->overSamp_acu = init_value;
    pDesc->level = level;
}

IIR_value_t Filter_IIR_Put(IIR_desc_t* pDesc, IIR_value_t newData) {
    pDesc->overSamp_acu += (newData - (pDesc->overSamp_acu >> pDesc->level));
    return (pDesc->overSamp_acu >> pDesc->level);
}

IIR_value_t Filter_IIR_Get(IIR_desc_t* pDesc ) {
    return (pDesc->overSamp_acu >> pDesc->level);
}

IIR_value_t Filter_IIR_over_samp_get(IIR_desc_t* pDesc ) {
    return (pDesc->overSamp_acu);
}

IIR_value_t Filter_IIR_level_get(IIR_desc_t* pDesc ) {
    return (pDesc->level);
}