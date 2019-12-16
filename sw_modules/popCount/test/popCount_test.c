#include "popCount_test.h"
#include "popCount.h"

#define TEST_CNT        (3)

uint_fast8_t test_array[TEST_CNT] = {
    5, 32, 30
};

uint_fast8_t ref_array[TEST_CNT] = {
    2, 1, 4
};

uint_fast8_t popCount_test(void){
    uint_fast8_t i;
    uint_fast8_t return_val = 0;
    uint_fast8_t result = 0;

    for(i = 0; i < TEST_CNT; ++i) {
        result = popCount(test_array[i]);
        if (result != ref_array[i])
        {
            /* test fail */
            return_val = i;
            break;
        }
    }
    return return_val;
}