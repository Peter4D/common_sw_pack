/*
 * error_check.c
 *
 * Created: 17. 07. 2017 12:13:40
 *  Author: peter.medvesek
 */ 

	// test_code --> cut_here
	//================================================================================
	//test: check_sum
	//uint8_t test_data[] = {44, 23, 61, 114, 62};  //hex: 0x2C, 0x17, 0x3D, 0x72, 0x3E
	//uint8_t error_check_out_data = 0;
	//error_check(test_data, sizeof(test_data), &error_check_out_data);	
	//================================================================================



#include "error_check.h"


#ifndef ERR_CHECK_METHOD
	#WARNING	"default error check use: CRC"
	#define ERR_CHECK_METHOD	(_USE_CRC)
#endif

#if (ERR_CHECK_METHOD == _USE_CRC)

	#include "crc8.h"
	
	void error_check(uint8_t* data, size_t size, uint8_t* error_check_out)
	{
		get_crc8(data, size, error_check_out);
	}
	
#endif // _USE_CRC

#if (ERR_CHECK_METHOD == _USE_CHECK_SUM)

	#include "check_sum.h"
	
	void error_check(uint8_t* data, size_t size, uint8_t* error_check_out)
	{
		check_sum(data, size, error_check_out);
	}

#endif // _USE_CHECK_SUM