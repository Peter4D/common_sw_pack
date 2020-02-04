#include "filter_IIR.h"


void Filter_IIR_Init(IIR_desc_t* pDesc, IIR_value_t* acu, uint8_t level) {
    pDesc->overSamp_acu = 0;
    pDesc->level = level;
}

void Filter_IIR_Put(IIR_desc_t* pDesc, IIR_value_t newData) {
    pDesc->overSamp_acu += (newData - (pDesc->overSamp_acu >> pDesc->level));
}

IIR_value_t Filter_IIR_Get(IIR_desc_t* pDesc ) {
    return (pDesc->overSamp_acu >> pDesc->level);
}