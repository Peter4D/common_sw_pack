/*
 * error_check.h
 *
 * Created: 17. 07. 2017 12:14:16
 *  Author: peter.medvesek
 */ 
// TEST: OK

#ifndef ERROR_CHECK_INCL_H_
#define ERROR_CHECK_INCL_H_

#include <stdint.h>
#include <stddef.h>

//============================= error_check_algorithms ============================
#define _USE_CRC		1
#define _USE_CHECK_SUM	2
//=================================================================================

//============================ error_check_algorithm_selected =====================
#define ERR_CHECK_METHOD	(_USE_CRC)
//=================================================================================

void error_check(uint8_t* data, size_t size, uint8_t* error_check_out);


#endif /* ERROR_CHECK_INCL_H_ */