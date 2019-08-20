/*
 * sw_stopWatch.c
 *
 * Created: 30. 11. 2017 12:02:17
 *  Author: peter.medvesek
 */ 

 #include "sw_stopWatch.h"

 #define SW_STOPWACH_nMAX	((uint8_t) 5)

 static sw_stopWatch_t* sw_stopWatch_inst[SW_STOPWACH_nMAX];
 static uint8_t slot_id = 0;

 //===============================================================
 // method declaration:
 
static  uint8_t     isRunning_method    (sw_stopWatch_t* pThis); // return status: running or stoped
static  void        start_method        (sw_stopWatch_t* pThis);
static  uint32_t    stop_method	        (sw_stopWatch_t* pThis); //return measured time
static  uint32_t    getLap_method       (sw_stopWatch_t* pThis);
static  void        _run                (sw_stopWatch_t* pThis);
//===============================================================
static uint8_t		get_slot			(sw_stopWatch_t* pThis);

//===============================================================

// for more convenient use ..all methods in the one place
const struct _sw_stopWatch_methods sw_stopWatch_methods = {
    &isRunning_method,
    &start_method,
    &stop_method,
    &getLap_method
};

//constructor
void  sw_stopWatch_init(sw_stopWatch_t* pThis) {
    get_slot(pThis);

    pThis->_active = 0;
    pThis->_time_cnt = 0;
    pThis->_lap_tm_cnt = 0;
    pThis->_lap_tm_cnt_old = 0;
}
//===============================================================


void _stopWatch_tick(void){
	uint8_t i = 0;
	for (;i < slot_id; ++i){
		_run(sw_stopWatch_inst[i]);
	}
}

static uint8_t get_slot (sw_stopWatch_t* pThis) {
    if (slot_id < SW_STOPWACH_nMAX)
    {
        sw_stopWatch_inst[slot_id] = pThis;
        // count number of software_timers
        ++slot_id;
        return 0;
    } else {
        //Assert_use(0)
        return 1; // max number of counter reached
    }
}


//===============================================================
// method implementations: 

static uint8_t isRunning_method (struct _sw_stopWatch* pThis) {
	return pThis->_active;
}

static void start_method (struct _sw_stopWatch* pThis) {
	pThis->_time_cnt = 0;
	pThis->_active = 1;
}

static uint32_t stop_method (struct _sw_stopWatch* pThis) {
	uint32_t temp = 0;
	temp = pThis->_time_cnt;
	pThis->_active = 0;
	pThis->_time_cnt = 0;
	return temp;
}

static uint32_t getLap_method (sw_stopWatch_t* pThis) {
	uint32_t temp;
	temp = pThis->_lap_tm_cnt_old;
	pThis->_lap_tm_cnt_old = pThis->_lap_tm_cnt;
	return (pThis->_lap_tm_cnt - temp);
}


/*
	@brief : _internal: meant to be called by sw_stopwatch_task
			 update stopWatches value
*/
static void _run (sw_stopWatch_t* pThis) {
	if (pThis->_active) {
		pThis->_time_cnt++;
		pThis->_lap_tm_cnt++;
	}
}

//===============================================================