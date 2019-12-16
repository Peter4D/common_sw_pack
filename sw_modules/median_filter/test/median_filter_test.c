#include "median_filter_test.h"
#include "median_filter.h"
#include <string.h>


/* size of medina filter window 
i.e. string of in data: 8 7 8 9 5 8 6 8 9 [ 10 23 7 9 5 ] median will be done on last 5
values in this example rezult will be:
sort: [ 10 23 7 9 5 ]  --> [ 5 7 9 10 23]
median: 9
*/
#define MEDIAN_WIN_SIZE     (5)

/* number of test data semples */
#define TEST_DATA_SIZE      (21)

/* median filter  channel 1 descriptor. you can have more then one */
median_desc_t median_ch1_desc;
median_data_t median_ch1_win[MEDIAN_WIN_SIZE];

median_value_t test_rezult_data[TEST_DATA_SIZE];

//=================================================================================================
/* test dataset is generated with MS excel */

/* this set of test value is [ PASS ] */
median_value_t test_data_1[TEST_DATA_SIZE]        =
{9,10,8,10,11,10,8,9,12,35,10,12,10,10,1,9,8,85,12,10,10};
median_value_t ref_rezult_data_1[TEST_DATA_SIZE]  =
{9,10,8,10,10,10,10,10,10,10,10,12,12,10,10,10,9,9,9,10,10};

/* this set of test value is [ PASS ] */
median_value_t test_data_2[TEST_DATA_SIZE]       =
{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
median_value_t ref_rezult_data_2[TEST_DATA_SIZE] =
{0,1,2,3,2,3,4,5,6,7,8 ,9 ,10,11,12,13,14,15,16,17,18};

/* this set of test value is [ PASS ] */
median_value_t test_data_3[TEST_DATA_SIZE]       =
{617,583,615,580,626,593,596,250,600,630,629,605,608,621,850,620,597,605,400,617,608};
median_value_t ref_rezult_data_3[TEST_DATA_SIZE] =
{617,583,615,580,615,593,596,593,596,596,600,605,608,621,621,620,620,620,605,605,605};
//=================================================================================================

typedef struct _test_dat_t{
    median_value_t *pTest_data;
    median_value_t *pRef_result;
}test_dat_t;

/* @note At the moment: Test data is manually selected in this structure. Improve can be done to
expand this test to automatically go through all test data sets.*/
test_dat_t test_dat = {
    test_data_3,
    ref_rezult_data_3
};

uint8_t test_median_filter(void) {
    uint8_t return_val = 0;
    uint8_t i;
    size_t size_in_uint8;
    uint8_t cmpr_result;

    /* initialize median filter channel */
    filter_median_init(&median_ch1_desc, median_ch1_win, MEDIAN_WIN_SIZE);

    for(i = 0; i < TEST_DATA_SIZE; i++) {
        /* function under test */
        test_rezult_data[i] = filter_median_get(&median_ch1_desc, test_dat.pTest_data[i]);
    }

    size_in_uint8 = TEST_DATA_SIZE * sizeof( test_dat.pRef_result[0]);
    cmpr_result = (uint8_t)memcmp(test_rezult_data, test_dat.pRef_result, size_in_uint8);

    if(cmpr_result != 0) {
        /* test fail */
        return_val = 1;
    }

    return return_val;
}