
#include "assert_gorenje.h"

//#define DEBUG

void assert_failed(uint8_t* file, uint32_t line);

static uint32_t _line;
static uint8_t* _file;

#ifndef NDEBUG

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
