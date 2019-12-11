/*
 * ring_buffer.c
 *
 * \created: 31. 05. 2017 12:11:23
 * \date modified:	27. 08. 2018 
 * \author: peter.medvesek
 */ 
#include <stdint.h>
#include "ring_buffer.h"
#include "assert_gorenje.h"


//=====================================================================================
/* methods declarations */ 
static void     push_method         (struct _ringBuff_t *pThis, uint8_t byte);
static uint16_t get_method          (struct _ringBuff_t *pThis);
static uint16_t get_nBytes_method   (struct _ringBuff_t *pThis);
static void     clear_method        (struct _ringBuff_t *pThis);
//=====================================================================================


const struct _ringBuff_methods_t ringBuff_methods = {
    &push_method,
    &get_method,
    &get_nBytes_method,	
    &clear_method
};

/* constructor */
void ringBuffer_init(ringBuff_t *pThis, uint8_t *data, size_t dataSize)
{
    uint16_t loop_itr = 0;

    pThis->_head = 0x00;
    pThis->_tail = 0x00;
    pThis->_data = data;
    pThis->_dataSize = dataSize;
    /* initialize ring buffer to 0 */
    for (loop_itr = 0; loop_itr < dataSize; ++loop_itr)
    {
        pThis->_data[loop_itr] = 0x00; 
        //*(pThis->_data + loop_itr) = 0x00;
    }
}

//=====================================================================================
/* methods */

/* store one element in to ring buffer */
static void push_method(ringBuff_t *pThis, uint8_t byte)
{
    uint16_t new_head = (pThis->_head+1) & (pThis->_dataSize - 1); // this "magic" make line buffer into ring buffer

    if(new_head != pThis->_tail)
    {
        pThis->_data[pThis->_head] = byte;
        pThis->_head = new_head;
    }
    else
    {
        // ERROR, can't override buffer
        assert(0);
    }  
}

/* return one element of ring buffer */
static uint16_t get_method(ringBuff_t *pThis)
{
	uint16_t ret_value = 0x00;
	if (pThis->_tail != pThis->_head)
	{
		ret_value = pThis->_data[pThis->_tail];
		pThis->_tail = (pThis->_tail + 1) & (pThis->_dataSize - 1); // this "magic" make line buffer into ring buffer
	} else {
		ret_value = 0;
	}
	return ret_value; 	
}

static uint16_t get_nBytes_method(ringBuff_t *pThis)
{
	return((pThis->_head - pThis->_tail) & (pThis->_dataSize - 1));
}

static void	clear_method(ringBuff_t *pThis){
	pThis->_head = pThis->_tail;
}
//=====================================================================================