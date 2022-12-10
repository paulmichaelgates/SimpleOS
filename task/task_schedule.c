/**
 *  task_scheduler.c
 * 
 *  provides task scheduling operations including main
 *  task scheduler task
 * 
 */

/* TI imports */
#include <msp430.h>
#include "msp430fr2355.h"

/* project imports */
#include "task_schedule.h"
#include "debug.h"
#include "utl_simple.h"

/*---------------------------------------
Variables
----------------------------------------*/
static list_t * s_task_list;

/*---------------------------------------
Procedures
----------------------------------------*/
static err_t insert_new_task(tcb_t * tcb);

void TSK_scheduler(void)
{
    /*  just blink led for now to show that this
        procedure is being called
    */
    toggle_led();

}

err_t task_create(tcb_t * tcb)
{
   return( insert_new_task(tcb) );
}

/*---------------------------------------
 task_bootup_sched()

boot up procedure for the task scheduler
----------------------------------------*/
err_t task_bootup_sched()
{
    /* configure timer */
	TB0CTL |= TBCLR;             /* clear timer on start (recomended) */
	TB0CTL |= MC__CONTINUOUS;    /* set as cont mode */
	TB0CTL |= TBSSEL__ACLK;      /* set clock as ACLK */
	TB0CTL |= TBIE;              /* set local enable for timer */

    /* initialize the task list to empty */
    s_task_list = NULL;

    return NO_ERR;
}

static err_t insert_new_task(tcb_t * tcb)
{
    /* local variables */
    list_t head;

    head.data = (void *)tcb;


    utl_list_insert_new_link(s_task_list, &head);

    return NO_ERR;
}