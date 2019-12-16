/**
 * @file ring_buffer.h
 * @author Peter Medvesek (peter.medvesek@gorenje.com)
 * @brief 
 * @version 0.1
 * @date 2017-05-31 | last update: 2019-12-12
 * 
 * @copyright Copyright (c) 2019 Gorenje d.o.o
 * 
 */
#ifndef RING_BUFFER_INCL_H_
#define RING_BUFFER_INCL_H_

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief type of data that ring buffer will store. this can not be changed on runtime
 * because C do not support templates like c++. More generic implementation can be achived 
 * by convert data type that are different then uint8_t to uint8_t but this will complicate 
 * the code and if not neccessery this implementation probably will be sufficient
 */
typedef uint8_t ringBuff_data_t;

typedef struct _ringBuff_t
{
	/* private data */
	uint16_t _head;
	uint16_t _tail;
	uint8_t* _pData;
    uint16_t _dataSize;
}ringBuff_t;

struct _ringBuff_methods_t 
{
/* public methods */
	void            (*push)        (struct _ringBuff_t *pThis, ringBuff_data_t newData);
	ringBuff_data_t (*get)         (struct _ringBuff_t *pThis);
	uint16_t        (*get_nBytes)  (struct _ringBuff_t *pThis);
	void            (*flush)       (struct _ringBuff_t *pThis);
};

/**
 * @brief structure containt ring buffer methods (functions)
 */
extern const struct _ringBuff_methods_t RingBuff;
 
/**
 * @brief constructor or. initializer
 * 
 * @param pThis     : pointer to instance(created object) of ring buffer struct
 * @param pData     : pointer to external data container for ring buffer to use
 * @param dataSize  : size of external container (must be size of 2^n i.e. 4,8,16,32,...)
 */
void ringBuffer_init(ringBuff_t *pThis, uint8_t *pData, size_t dataSize);


#endif /* RING_BUFFER_INCL_H_ */