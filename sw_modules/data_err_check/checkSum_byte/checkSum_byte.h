/*
 * checkSum_byte_incl.h
 *
 * Created: 17. 07. 2017 11:56:00
 *  Author: peter.medvesek
 */ 
// TEST: OK

#ifndef CHECKSUM_BYTE_INCL_H_
#define CHECKSUM_BYTE_INCL_H_


#include <stdint.h>
#include <stddef.h>

void get_checkSum_byte(const uint8_t* data, size_t data_size, uint8_t* checkSum_out);


#endif /* CHECKSUM_BYTE_INCL_H_ */