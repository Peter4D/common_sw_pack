/*
 * checkSum_byte.c
 *
 * Created: 17. 07. 2017 11:55:31
 *  Author: peter.medvesek
 */ 


#include "checkSum_byte_incl.h"


void get_checkSum_byte(const uint8_t* data, size_t data_size, uint8_t* checkSum_out)
{
	uint8_t checkSum_temp = 0; // temp. for calculation
	uint8_t loop_i = 0;
	for (loop_i = 0; loop_i < data_size; ++loop_i)
	{
		checkSum_temp += data[loop_i];
	}
	//checkSum_temp = (checkSum_temp - 0xFF) + 1;
	checkSum_temp = ~checkSum_temp + 1;
	*checkSum_out = checkSum_temp;
}