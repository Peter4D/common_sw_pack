/**
 * @file checkSum_byte.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 0.1
 * @date 2017-07-17
 * 
 * @copyright Copyright (c) 2019 Gorenje d.o.o
 * 
 */
#ifndef CHECKSUM_BYTE_INCL_H_
#define CHECKSUM_BYTE_INCL_H_


#include <stdint.h>
#include <stddef.h>

void get_checkSum_byte(const uint8_t* data, size_t data_size, uint8_t* checkSum_out);


#endif /* CHECKSUM_BYTE_INCL_H_ */