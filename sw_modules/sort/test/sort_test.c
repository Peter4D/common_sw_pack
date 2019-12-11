#include "sort_wrap.h"
#include "sort_wrap.h"
#include <string.h>

#define TEST_DATA_SIZE      (20u)

int8_t test_I8_data[TEST_DATA_SIZE] = 
{ 23,-49,27,3,6,-4,-19,-17,9,8,40,-1,7,48,-3,44,-42,-33,-16,-21 };

int8_t test_sort_I8_data[TEST_DATA_SIZE] = 
{ -49,-42,-33,-21,-19,-17,-16,-4,-3,-1,3,6,7,8,9,23,27,40,44,48 };


/* test OK: 2019_11_29 */
uint8_t test_sort(void) {
    uint8_t cmpr_res = 255;
    uint8_t return_val = 0;
    uint8_t cmpr_size = sizeof(test_I8_data)/sizeof(test_I8_data[0]);

    /* function under test */
    sort_int8(test_I8_data, TEST_DATA_SIZE);

    cmpr_res = memcmp(test_I8_data, test_sort_I8_data, cmpr_size);
    if(0 != cmpr_res) {
        /* test fail */
        return_val = 1;
    }

    return return_val;
}