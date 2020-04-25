
#include "scheduler_s1.h"

/* dependencies */
#include "assert_hot_sw_pack.h"
//#include "rde_debug.h"

/** 
 * @todo this is temporary solution this setting should be in different file like rde_app_cfg.h
*/
//#define ASSERT_HOT_SW_PACK(expr) RDE_ASSERT(expr)

#ifndef ASSERT_HOT_SW_PACK
#define ASSERT_HOT_SW_PACK(expr) ((void)0)
#endif



typedef struct
{
    void (*task_run)(void);
    uint32_t tm_periode;
    uint32_t tm_elapsed;
} task_t;

/**
 * @brief main task queue
 */
static task_t tasks_queue[SCHEDULER_TASK_MAX];

/**
 * @brief single shot task queue those calls are executed as soon as possible 
 */
static void (*singleShot_queue[SCHEDULER_SINGLE_MAX])(void);


//=============================================================
// method declaration:

/**
 * @brief This run the scheduler (must be called from Hardware timer) 
 */
void run(void);

/**
 * @brief This method executing tasks. This must be called in main thread [ in while(1) loop ]
 */
void task_exe(void);

/**
 * @brief Add new task in execution queue
 * 
 * @param task      : function pointer to task funcion
 * @param periode   : execution periode of this task function
 */
void add_task(void (*task)(void), uint32_t periode);

/**
 * @brief add new single shot task or function call. This is executed only once and is removed from queue
 * 
 * @param single_fptr   : Function pointer to function that will be executed as single shot 
 */
void new_singleShot(void (*single_fptr)(void));

void _dummy(void);
//=============================================================

/* if this systax do not compile: remove: ( .xy = ) */
scheduler_t Scheduler = {
    .add_task       = &add_task,
    .new_singleShot = &new_singleShot,
    .run            = &run,
    .task_exe       = &task_exe,

    ._task_active_F         = 0,
    ._single_active_F       = 0,
    ._active_task_ID        = 0,
    ._task_cnt              = 0,
    ._single_shot_task_cnt  = 0,
    ._fail_cnt              = 0 
};


//=============================================================
// methods implementations:
void run(void)
{
    static uint8_t task_select = 0;
    task_t* p_task;
    uint8_t i = 0;

    /* Tasks timing handling */
    for (i = 0; i < Scheduler._task_cnt; ++i)
    {
        p_task = &tasks_queue[i];
        p_task->tm_elapsed += SCHEDULER_TICK_MS;
    }

    if (Scheduler._single_shot_task_cnt > 0)
    {
        Scheduler._single_active_F = 1;
    }

    
}

void task_exe(void)
{
    task_t *p_task;

    // single shot events
    if (Scheduler._single_active_F)
    {
        --Scheduler._single_shot_task_cnt;
        
        singleShot_queue[Scheduler._single_shot_task_cnt]();
        
        Scheduler._single_active_F = 0;
    }

    for(uint8_t i = 0; i < Scheduler._task_cnt; ++i) {
        p_task = &tasks_queue[i];
        if(p_task->tm_elapsed >= p_task->tm_periode) {
            p_task->task_run();
            p_task->tm_elapsed = 0;
        }
    }

}

void add_task(void (*p_task)(void), uint32_t periode)
{
    if (Scheduler._task_cnt < SCHEDULER_TASK_MAX)
    {
        tasks_queue[Scheduler._task_cnt].tm_periode = periode;
        tasks_queue[Scheduler._task_cnt].tm_elapsed += Scheduler._task_cnt; // to offset the task
        tasks_queue[Scheduler._task_cnt].task_run = p_task;
        ++Scheduler._task_cnt;
    }
    else
    {
        // max task reached
        //RDE_ASSERT(0); 
        ASSERT_HOT_SW_PACK(0);
    }
}

void new_singleShot(void (*single_fptr)(void))
{
    singleShot_queue[Scheduler._single_shot_task_cnt] = single_fptr;

    if (Scheduler._single_shot_task_cnt < SCHEDULER_SINGLE_MAX)
    {
        ++Scheduler._single_shot_task_cnt;
    }
    else
    {
        // max number of unhandled single shot (or event )
        ASSERT_HOT_SW_PACK(0); 
    }
}

void _dummy(void)
{
    while (1)
        ;
}
//=============================================================