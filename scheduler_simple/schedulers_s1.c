/*
 * scheduler_2.c
 *
 * Created: 11. 12. 2017 10:19:18
 *  Author: peter.medvesek
 */

#include "scheduler_2.h"
#include "debug_incl.h"

#define TASK_MAX (10)
#define SINGLE_MAX (10)

static task_t tasks_queue[TASK_MAX];
static void (*singleShot_queue[SINGLE_MAX])(void);

static uint8_t task_cnt = 0;
static uint8_t singleShot_cnt = 0;

scheduler_t *scheduler = 0; // pointer to scheduler for user to use

//=============================================================
// method declaration:
void run_method(void);
void task_exe_method(void);
void add_task_method(void (*task)(void), uint32_t periode);
void new_singleShot_method(void (*single_fptr)(void));

void _dummy(void);
//=============================================================

static scheduler_t _scheduler = {
    .add_task = &add_task_method,
    .new_singleShot = &new_singleShot_method,
    .run = &run_method,
    .task_exe = &task_exe_method,

    ._task_active_F = 0,
    ._single_active_F = 0,
    ._active_task_ID = 0

};

scheduler_t *sceduler_Init(void)
{
    return &_scheduler;
}

//=============================================================
// methods implementations:
void run_method(void)
{
    //static uint8_t taskEvent_switch = 0;
    static uint8_t task_select = 0;
    task_t *task;
    uint8_t i = 0;

    /* task timing handling */
    for (i = 0; i < task_cnt; ++i)
    {
        task = &tasks_queue[i];
        task->tm_elapsed++;
    }

    if (_scheduler._single_active_F == 0 && _scheduler._task_active_F == 0)
    {
        for (i = 0; i < task_cnt; ++i)
        {
            task = &tasks_queue[task_select];
            if (task->tm_elapsed > task->tm_periode)
            {
                task->tm_elapsed = 0;
                _scheduler._task_active_F = 1;
                _scheduler._active_task_ID = task_select;
                break;
                // task->task_run();
            }

            if (task_select < (task_cnt - 1))
            {
                ++task_select;
            }
            else
            {
                task_select = 0;
            }
        }

        if (singleShot_cnt > 0)
        {
            _scheduler._single_active_F = 1;
        }
    }
    else
    {
        // task  take to much time
        //Assert_user(0);
    }
}

void task_exe_method(void)
{
    task_t *task;

    // single shot events
    if (_scheduler._single_active_F)
    {
        singleShot_queue[singleShot_cnt]();
        --singleShot_cnt;
        _scheduler._single_active_F = 0;
    }

    if (_scheduler._task_active_F)
    {
        task = &tasks_queue[_scheduler._active_task_ID];
        task->task_run();
        _scheduler._task_active_F = 0;
    }
}

void add_task_method(void (*task)(void), uint32_t periode)
{
    if (task_cnt < TASK_MAX)
    {
        tasks_queue[task_cnt].tm_periode = periode;
        tasks_queue[task_cnt].tm_elapsed += task_cnt; // to offset the task
        tasks_queue[task_cnt].task_run = task;
        ++task_cnt;
    }
    else
    {
        Assert_user(0); // max task reached
    }
}

void new_singleShot_method(void (*single_fptr)(void))
{
    singleShot_queue[singleShot_cnt] = single_fptr;

    if (singleShot_cnt < SINGLE_MAX)
    {
        ++singleShot_cnt;
    }
    else
    {
        Assert_user(0); // max number of unhandled single shot (or event )
    }
}

void _dummy(void)
{
    while (1)
        ;
}
//=============================================================