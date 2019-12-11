/*!
 *  \file			ring_buffer.h
 *
 *  \created:		31. 05. 2017 12:11:42
 *	\date modified:	27. 08. 2018 
 *  \author:		peter.medvesek
 */ 


#ifndef RING_BUFFER_INCL_H_
#define RING_BUFFER_INCL_H_

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

/* warning: because of implementation RING_BUFF_SIZE must be 2^n; look --> store_methode */
//#define RING_BUFF_SIZE  128 

typedef struct _ringBuff_t
{
	/* private data */
	uint16_t _head;
	uint16_t _tail;
	uint8_t* _data;
    uint16_t _dataSize;
}ringBuff_t;

struct _ringBuff_methods_t 
{
/* public methods */
	void        (*push)        (struct _ringBuff_t *pThis, uint8_t byte);
	uint16_t    (*get)         (struct _ringBuff_t *pThis);
	uint16_t    (*get_nBytes)  (struct _ringBuff_t *pThis);
	void        (*clear)       (struct _ringBuff_t *pThis);
};

extern const struct _ringBuff_methods_t ringBuff_methods;

// constructor or. initializer
void ringBuffer_init(ringBuff_t *pThis, uint8_t *data, size_t dataSize);


#endif /* RING_BUFFER_INCL_H_ */