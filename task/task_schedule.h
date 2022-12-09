/*

task_schedule.h

Description:   Provides defintions for the task scheduler

*/
#ifndef TASK_SCHEDLUER_H
#define TASK_SCHEDLUER_H

/*---------------------------------------
 Includes
----------------------------------------*/

#include "utl_types.h"

/*---------------------------------------
 Types
----------------------------------------*/
typedef struct
{
     void (*task_proc)(int);
}task_def_t;

/*---------------------------------------
 Procedures
----------------------------------------*/

/*---------------------------------------
 task_init.c
----------------------------------------*/
err_t task_init();

err_t task_bootup_sched();

#endif /* TASK_SCHEDLUER_H */