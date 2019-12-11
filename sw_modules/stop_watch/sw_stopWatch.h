/*
 * sw_stopWatch.h
 *
 * Created: 30. 11. 2017 12:02:29
 *  Author: peter.medvesek
 */ 


#ifndef SW_STOPWATCH_H_
#define SW_STOPWATCH_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct _sw_stopWatch{
//private:
    uint8_t     _active;
    uint32_t    _time_cnt;
    uint32_t    _lap_tm_cnt;
    uint32_t    _lap_tm_cnt_old;
}sw_stopWatch_t;

struct _sw_stopWatch_methods{
    //public:
    uint8_t     (*isRunning)(struct _sw_stopWatch* pThis); // return status: running or stoped
    void        (*start)    (struct _sw_stopWatch* pThis);
    uint32_t    (*stop)     (struct _sw_stopWatch* pThis); //return measured time
    uint32_t    (*getLap)   (struct _sw_stopWatch* pThis); //return length of interval/ lap between to successive call
};

extern const struct _sw_stopWatch_methods sw_stopWatch_methods;

void sw_stopWatch_init(sw_stopWatch_t* pThis); //constructor
// drive all instances of software stop  watch. (call periodically in e.g. HW timer interrupt every 1ms )
void _stopWatch_tick(void); 


#endif /* SW_STOPWATCH_H_ */