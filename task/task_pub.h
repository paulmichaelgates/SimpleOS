/*

task_schedule.h

Description:   Provides defintions for the task scheduler

*/
#ifndef TASK_SCHEDLUER_H
#define TASK_SCHEDLUER_H

/*---------------------------------------
 Includes
----------------------------------------*/

#include "utl_simple.h"

/*---------------------------------------
 Types
----------------------------------------*/
typedef struct
{
     void ( * task_proc )( void );
}tcb_t;
 
/*---------------------------------------
 Procedures
----------------------------------------*/

/*---------------------------------------
 task_schedule.c
----------------------------------------*/
void TSK_scheduler
     (
     void
     );

/*---------------------------------------
 task_init.c
----------------------------------------*/
tcb_t * TSK_get_current
     (
     void
     );

/*---------------------------------------
 task_init.c
----------------------------------------*/
err_t task_init();

err_t task_bootup_sched();

#endif /* TASK_SCHEDLUER_H */