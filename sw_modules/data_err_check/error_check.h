/**
 * @file error_check.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 0.1
 * @date 2017-07-17
 * 
 * @copyright Copyright (c) 2019 Gorenje d.o.o
 * 
 */

#ifndef ERROR_CHECK_INCL_H_
#define ERROR_CHECK_INCL_H_

#include <stdint.h>
#include <stddef.h>

//============================= error_check_algorithms ============================
#define _USE_CRC        1
#define _USE_CHECK_SUM  2
//=================================================================================

//============================ error_check_algorithm_selected =====================
#define ERR_CHECK_METHOD    (_USE_CRC)
//=================================================================================


/**
 * @brief calculate error check value use algorithm specified with ERR_CHECK_METHOD
 * 
 * @param pData             : pointer to input data  
 * @param size              : size of input data
 * @param pError_check_out  : pointer to location where calculated error_check value will be put
 */
void error_check(const uint8_t* const  pData, size_t size, uint8_t* pError_check_out);


#endif /* ERROR_CHECK_INCL_H_ */