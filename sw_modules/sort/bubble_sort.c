#include "bubble_sort.h"
#include "median_filter.h"
#include <string.h>


void bubble_sort (void* pBuffer, size_t nSize, size_t data_width, uint8_t (*pCompar)(const void*, const void*)){
    uint8_t i,j,k;
    uint8_t *ptr = pBuffer;
    /* #warnign: max size of single element of data stucture !*/
    uint8_t tmp[16];

    if(nSize < 2 || data_width == 0)return;

    /* bubble sorf iteration loop */
    for(i = (nSize-1); i > 0; i--) 
    {
        /* bubble sort buffer walk loop */
        for(j = 0; j < i; j++) 
        {
            k = pCompar((void*)(ptr + data_width * (j)), (void*)(ptr + data_width * (j+1)) );
            if(k > 0)
            {
                memcpy(tmp, ptr + data_width*(j), data_width);
                memcpy(ptr + data_width*(j), ptr + data_width*(j+1), data_width);
                memcpy(ptr + data_width * (j+1), tmp, data_width);
            }
        }
    }
}