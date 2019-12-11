
#include "assert_stm8_gorenje.h"


//#define DEBUG

void assert_failed(uint8_t* file, uint32_t line);

static uint32_t _line;
static uint8_t* _file;


#undef assert
#ifndef NDEBUG

//#ifdef DEBUG
//#if ( USE_ASSERT == 1u )

void assert_failed(uint8_t* file, uint32_t line)
{
	_line = line;
	_file = file;
    while(1){}
}


#else
// empty function !
void assert_failed(uint8_t * file, uint32_t line) 
{
    (void)file;
    (void)line;
}

#endif
