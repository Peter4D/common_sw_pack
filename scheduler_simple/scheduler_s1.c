
#include "scheduler_s1.h"
#include <stddef.h>
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


__attribute__((weak)) void scheduler_debug_msg_hook(const char* const prefix_msg, char* const debug_msg) {
    (void)prefix_msg;
    (void)debug_msg;
    /* user should provide definition for function at app level */
    //void debug_msg(char* str_prefix, char* str);
}

static const char debug_prefix_str[] = "scheduler:";

typedef struct
{
    void (*task)(void* p_arg);
    void* p_arg;
    uint32_t tm_periode;
    uint32_t tm_elapsed;
} task_t;

typedef struct _singleShot_queue_t {
    void(*exe)(void* p_arg);
    void* p_arg;
}singleShot_queue_t;

/**
 * @brief main task queue
 */
static task_t tasks_queue[SCHEDULER_TASK_MAX];

/**
 * @brief single shot task queue those calls are executed as soon as possible 
 */
singleShot_queue_t singleShot_queue[SCHEDULER_SINGLE_MAX] = {0};




void Scheduler_init(void) {

    /* at the momnet nothing to do :) */

    scheduler_debug_msg_hook(debug_prefix_str, "init");
}

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

/**
 * @brief  Add new task in execution queue
 * 
 * @param task      : function pointer to task funcion.
 * @param periode   : execution periode of this task function.
 * @return uint8_t  : task id. use this id if task need to be removed with remove_task.
 */
uint8_t add_task(void (*task)(void* p_arg), uint32_t periode, void* p_task_arg);

/**
 * @brief Remove task from schedule table 
 * 
 * @param task_id : task id that will be removed from schedule table.
 */
void remove_task(uint8_t task_id);

/**
 * @brief Get the active task id handle. Call this inside task function
 * to obtain this task handle. handle can be then use to remove task 
 * 
 * @return uint8_t task handle
 */
uint8_t get_active_task_id(void);

/**
 * @brief add new single shot task or function call. This is executed only once and is removed from queue
 * 
 * @param single_fptr   : Function pointer to function that will be executed as single shot 
 */
void new_singleShot(void (*single_fptr)(void* p_arg), void* p_arg);

static uint8_t get_function_is_listed(void (*task)(void));

void _dummy(void);
//=============================================================

scheduler_t Scheduler = {
    .add_task           = &add_task,
    .remove_task        = &remove_task,
    .get_active_task_id = &get_active_task_id,
    .get_function_is_listed = &get_function_is_listed,
    .new_singleShot     = &new_singleShot,
    .run                = &run,
    .task_exe           = &task_exe,

    ._task_active_F         = 0,
    ._active_task_ID        = 0,
    ._task_cnt              = 0,
    ._single_shot_task_cnt  = 0,
    ._fail_cnt              = 0,
};

//=============================================================
// methods implementations:
void run(void)
{
    task_t* p_task;
    
    /* Tasks timing handling */
    for(uint8_t i = 0; i < SCHEDULER_TASK_MAX; ++i)
    {
        p_task = &tasks_queue[i];
        if(p_task->task != NULL) {

            p_task->tm_elapsed += SCHEDULER_TICK_MS;
        }
    }
}

void task_exe(void)
{
    task_t *p_task;

    for(uint8_t i = 0; i < SCHEDULER_TASK_MAX; ++i) {
        
        p_task = &tasks_queue[i];
        if(p_task->task != NULL) {

            if(p_task->tm_elapsed >= p_task->tm_periode) {
                Scheduler._active_task_ID = i;
                p_task->task(p_task->p_arg);
                p_task->tm_elapsed = 0;
            }
        }
    }

    // single shot events
    if (Scheduler._single_shot_task_cnt > 0)
    {
        singleShot_queue_t* p_single_exe;

        --Scheduler._single_shot_task_cnt;
        p_single_exe = &singleShot_queue[Scheduler._single_shot_task_cnt];

        p_single_exe->exe(p_single_exe->p_arg);
    }
}

uint8_t add_task(void (*task)(void* p_arg), uint32_t periode, void* p_task_arg)
{
    task_t* p_slot;
    uint8_t task_id = SCHEDULER_TASK_ID_INVALID;

    if(Scheduler._task_cnt >= SCHEDULER_TASK_MAX) {
        // max task reached
        //ASSERT_HOT_SW_PACK(0);
        scheduler_debug_msg_hook(debug_prefix_str, "task alloc. fail");
    }else {
        for(uint8_t i = 0; i < SCHEDULER_TASK_MAX; ++i){
            p_slot = &tasks_queue[i];

            if(p_slot->task == NULL) {
                p_slot->task = task;
                p_slot->tm_periode = periode;
                p_slot->p_arg = p_task_arg;
                
                p_slot->tm_elapsed = 0;

                ++Scheduler._task_cnt;
                task_id = i;
                break;
            }
        }
    }

    return task_id;
}

static uint8_t get_function_is_listed(void (*task)(void)) {
    uint8_t ret_val = 0;

    for(uint8_t i = 0; i < SCHEDULER_TASK_MAX; ++i) {
        task_t* p_task = &tasks_queue[i];

        if(p_task->task == task) {
            ret_val = 1;
            break;
        }
    }

    return ret_val;
}

void remove_task(uint8_t task_id) {

    //ASSERT_HOT_SW_PACK(task_id < SCHEDULER_TASK_MAX);
    
    if(task_id < SCHEDULER_TASK_MAX) {
        tasks_queue[task_id].task = NULL;
        --Scheduler._task_cnt;
    }else {
        scheduler_debug_msg_hook(debug_prefix_str, "try remove invalid task ID");
    }
}

void new_singleShot(void (*single_fptr)(void* p_arg), void* p_arg)
{
    if(Scheduler._single_shot_task_cnt < SCHEDULER_SINGLE_MAX) {
        singleShot_queue[Scheduler._single_shot_task_cnt].exe = single_fptr;
        singleShot_queue[Scheduler._single_shot_task_cnt].p_arg = p_arg;
        
        ++Scheduler._single_shot_task_cnt;
    }else {
        // max number of unhandled single shot (or event )
        //ASSERT_HOT_SW_PACK(0); 
        scheduler_debug_msg_hook(debug_prefix_str, "single shot alloc. fail");
    }
}

uint8_t get_active_task_id(void) {
    return Scheduler._active_task_ID;
}

void _dummy(void)
{
    while (1)
        ;
}
//=============================================================