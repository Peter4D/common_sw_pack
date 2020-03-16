
#include <stdint.h>
#include "ring_buffer.h"
#include "assert_hot_sw_pack.h"


//=====================================================================================
/* methods declarations */ 
/**
 * @brief store new data object in to ring buffer
 * @param pThis     : pointer to instance of ring buffer structure
 * @param newData   : new data object that will be stored (if used byte then one byte is pushed into buffer)
 */
static void push(struct _ringBuff_t *pThis, uint8_t newData);

/**
 * @brief Get one data element off the buffer 
 * 
 * @param pThis             : pointer to instance of ring buffer structure
 * @return ringBuff_data_t  : return data element value from buffer (FIFO)
 */
static ringBuff_data_t get(struct _ringBuff_t *pThis);

/**
 * @brief get number of data elements currently stored in buffer
 * 
 * @param pThis     : pointer to instance of ring buffer structure
 * @return uint16_t : number of data element stored in buffer
 */
static uint16_t get_nBytes(struct _ringBuff_t *pThis);

/**
 * @brief flush buffer (delete) all its contents
 * 
 * @param pThis     : pointer to instance of ring buffer structure
 */
static void flush(struct _ringBuff_t *pThis);
//=====================================================================================

const struct _ringBuff_methods_t RingBuff = {
    &push,
    &get,
    &get_nBytes,	
    &flush
};

/* constructor */
void RingBuff_init(ringBuff_t *pThis, ringBuff_data_t *pData, size_t dataSize)
{
    uint16_t loop_itr = 0;

    pThis->_head = 0x00;
    pThis->_tail = 0x00;
    pThis->_pData = pData;
    pThis->_dataSize = dataSize;
    /* initialize ring buffer to 0 */
    for (loop_itr = 0; loop_itr < dataSize; ++loop_itr)
    {
        pThis->_pData[loop_itr] = 0x00; 
        //*(pThis->_pData + loop_itr) = 0x00;
    }
}

//=====================================================================================
/* methods implementation */

static void push(ringBuff_t *pThis, ringBuff_data_t newData)
{
    /* this "magic" make line buffer into ring buffer */
    uint16_t new_head = (pThis->_head + 1) & (pThis->_dataSize - 1); 

    if(new_head != pThis->_tail)
    {
        pThis->_pData[pThis->_head] = newData;
        pThis->_head = new_head;
    }
    else
    {
        // ERROR, can't override buffer
        ASSERT_HOT_SW_PACK(0);
    }  
}

static ringBuff_data_t get(ringBuff_t *pThis)
{
	ringBuff_data_t ret_value = 0;

	if (pThis->_tail != pThis->_head)
	{
		ret_value = pThis->_pData[pThis->_tail];
        /* this "magic" make line buffer into ring buffer */
		pThis->_tail = (pThis->_tail + 1) & (pThis->_dataSize - 1); 
	} else {
		ret_value = 0;
	}
	return ret_value;
}

static uint16_t get_nBytes(ringBuff_t *pThis)
{
	return((pThis->_head - pThis->_tail) & (pThis->_dataSize - 1));
}

static void	flush(ringBuff_t *pThis){
	pThis->_head = pThis->_tail;
}
//=====================================================================================