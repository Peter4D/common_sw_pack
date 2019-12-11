#include "num_str_convert_test.h"
#include <string.h>

typedef struct _xTest_str2num_t {
    uint8_t test_id;
    uint8_t *pStr;
    int32_t number;
}xTest_str2num_t;


uint8_t test_str2num(void){
    xTest_str2num_t const tests[] = {
        { 0, "-123456", -123456 },
        { 1, "123456" , 123456  },
        { 2, "1a456"  , 0       }
    };
    uint8_t nTest = sizeof(tests)/sizeof(tests[0]);
    int32_t result = 0;
    uint8_t test_result = 0x00;
    uint8_t i;
    
    for(i = 0; i < nTest; i++) {
        result = str2num(tests[i].pStr);
        if(result != tests[i].number) {
            /* test fail: encode test id as bitField */
            test_result |= (uint8_t)(1 << tests[i].test_id);
        }
    }
    
    return test_result;
}

uint8_t test_num2str(void){
#define STR_SIZE        (15u)

    xTest_str2num_t const tests[] = {
        { 0, "-123456", -123456 },
        { 1, "123456" , 123456  },
    };
    uint8_t nTest = sizeof(tests)/sizeof(tests[0]);
    uint8_t result_str[STR_SIZE] = {0};
    uint8_t const empty_str[STR_SIZE] = {0};
    uint8_t test_result = 0x00;
    uint8_t i;
    
    for(i = 0; i < nTest; i++) {
        /* clear string at every iteration */
        memcpy(result_str, empty_str, STR_SIZE);

        num2str(tests[i].number, result_str);

        if(0 != strcmp(result_str, tests[i].pStr)) {
            /* test fail: encode test id as bitField */
            test_result |= (uint8_t)(1 << tests[i].test_id);
        }
    }
    return test_result;
}