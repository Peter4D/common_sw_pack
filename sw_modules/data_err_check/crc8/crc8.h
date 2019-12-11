/*
 * crc8_incl.h
 *
 * Created: 29. 06. 2017 14:52:25
 *  Author: peter.medvesek
 */ 
// TEST: OK

#ifndef CRC8_INCL_H_
#define CRC8_INCL_H_

#include <stdint.h>
#include <stddef.h>

void get_crc8(const uint8_t* data, size_t size, uint8_t* crc_out);


#endif /* CRC8_INCL_H_ */