
#include "scheduler_classB.h"
#include <stddef.h>
/* dependencies */
#include "assert_hot_sw_pack.h"
#include "complement_data.h"



#ifndef ASSERT_HOT_SW_PACK
#define ASSERT_HOT_SW_PACK(expr) ((void)0)
#endif


__attribute__((weak)) void scheduler_debug_msg_hook(const char* const prefix_msg, char* const debug_msg) {
    (void)prefix_msg;
    (void)debug_msg;
    /* user should provide definition for function at app level */
    //void debug_msg(char* str_prefix, char* str);
}

static const char debug_prefix_str[] = "sched.(B):";

typedef struct
{
    void (*task)(void);
    uint32_t tm_periode;
    uint32_t tm_elapsed;
} task_t;

typedef struct _singleShot_queue_t {
    void(*exe)(void* p_arg);
    void* p_arg;
}singleShot_queue_t;


typedef struct _sched_CB_t {
    /** @brief main task queue */
    task_t tasks_queue[SCHEDULER_TASK_MAX];
    /** @brief main task queue */
    singleShot_queue_t singleShot_queue[SCHEDULER_SINGLE_MAX];

    uint8_t _task_active_F;
    uint8_t _active_task_ID;
    uint8_t _task_cnt;              // only for debug 
    uint8_t _single_shot_task_cnt;
    uint8_t _fail_cnt;

    //void (*inv_var_fail_cb)(void* context);

}sched_CB_t;

static sched_CB_t m;
static sched_CB_t m_inv;

void Scheduler_init(void) {

    //m.inv_var_fail_cb = NULL;

    data_complement_set(&m, &m_inv, sizeof(m));

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
uint8_t add_task(void (*task)(void), uint32_t periode);

/**
 * @brief Remove taks from schedule table 
 * 
 * @param task_id : taks id that will be removed from schedule table.
 */
void remove_task(uint8_t task_id);

/**
 * @brief Get the active task id handle. Call this inside task function
 * to obtain this task handl. handle can be then use to removet task 
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

void _dummy(void);
//=============================================================

const scheduler_t Scheduler = {
    .add_task           = &add_task,
    .remove_task        = &remove_task,
    .get_active_task_id = &get_active_task_id,
    .new_singleShot     = &new_singleShot,
    .run                = &run,
    .task_exe           = &task_exe,
};


static void inv_data_test(const void* const p_data_in, const void* const p_data_in_inv, size_t size) {

    if(data_complement_test(p_data_in, p_data_in_inv, size) != 0) {
        /* fail */
        scheduler_debug_msg_hook(debug_prefix_str, "inv_var err");
        while(1);
    }
}

//=============================================================
// methods implementations:
/* ISR context ! */
void run(void)
{
    task_t* p_task;
    task_t* p_task_inv;

    /* Tasks timing handling */
    for(uint8_t i = 0; i < SCHEDULER_TASK_MAX; ++i)
    {
        p_task = &m.tasks_queue[i];
        p_task_inv = &m_inv.tasks_queue[i];

        if(p_task->task != NULL) {
            inv_data_test(p_task, &p_task_inv, sizeof(task_t));
            p_task->tm_elapsed += SCHEDULER_TICK_MS;
            data_complement_set(p_task, &p_task_inv, sizeof(task_t));
        }
    }
}

void task_exe(void)
{
    task_t *p_task;

    for(uint8_t i = 0; i < SCHEDULER_TASK_MAX; ++i) {
        
        p_task = &m.tasks_queue[i];
        if(p_task->task != NULL) {

            if(p_task->tm_elapsed >= p_task->tm_periode) {
                inv_data_test(&m, &m_inv, sizeof(m));

                m._active_task_ID = i;
                p_task->task();
                p_task->tm_elapsed = 0;

                data_complement_set(&m, &m_inv, sizeof(m));
            }
        }
    }

    // single shot events
    if (m._single_shot_task_cnt > 0)
    {
        singleShot_queue_t* p_single_exe;

        inv_data_test(&m, &m_inv, sizeof(m));

        --m._single_shot_task_cnt;
        p_single_exe = &m.singleShot_queue[m._single_shot_task_cnt];

        p_single_exe->exe(p_single_exe->p_arg);

        data_complement_set(&m, &m_inv, sizeof(m));
    }
}

uint8_t add_task(void (*p_task)(void), uint32_t periode)
{
    task_t* p_slot;
    uint8_t task_id = SCHEDULER_TASK_ID_INVALID;

    inv_data_test(&m, &m_inv, sizeof(m));

    if(m._task_cnt >= SCHEDULER_TASK_MAX) {
        // max task reached
        //ASSERT_HOT_SW_PACK(0);
        scheduler_debug_msg_hook(debug_prefix_str, "task alloc. fail");
    }else {
        for(uint8_t i = 0; i < SCHEDULER_TASK_MAX; ++i){
            p_slot = &m.tasks_queue[i];

            if(p_slot->task == NULL) {
                p_slot->task = p_task;
                p_slot->tm_periode = periode;
                p_slot->tm_elapsed = 0;

                ++m._task_cnt;
                task_id = i;
                break;
            }
        }
    }

    data_complement_set(&m, &m_inv, sizeof(m));

    return task_id;
}

void remove_task(uint8_t task_id) {

    //ASSERT_HOT_SW_PACK(task_id < SCHEDULER_TASK_MAX);
    inv_data_test(&m, &m_inv, sizeof(m));    

    if(task_id < SCHEDULER_TASK_MAX) {
        m.tasks_queue[task_id].task = NULL;
        --m._task_cnt;
    }

    data_complement_set(&m, &m_inv, sizeof(m));    
}

void new_singleShot(void (*single_fptr)(void* p_arg), void* p_arg)
{
    inv_data_test(&m, &m_inv, sizeof(m));

    if(m._single_shot_task_cnt < SCHEDULER_SINGLE_MAX) {
        m.singleShot_queue[m._single_shot_task_cnt].exe = single_fptr;
        m.singleShot_queue[m._single_shot_task_cnt].p_arg = p_arg;
        
        ++m._single_shot_task_cnt;
    }else {
        // max number of unhandled single shot (or event )
        //ASSERT_HOT_SW_PACK(0); 
        scheduler_debug_msg_hook(debug_prefix_str, "single shot alloc. fail");
    }

    data_complement_set(&m, &m_inv, sizeof(m));

}

uint8_t get_active_task_id(void) {

    inv_data_test(&m, &m_inv, sizeof(m));

    return m._active_task_ID;
}

void _dummy(void)
{
    while (1)
        ;
}
//=============================================================