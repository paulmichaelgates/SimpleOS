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

#define TSK_BGKND_STACK_SIZE 64

/* background task stack */
static uint16 tsk_bkgn_stack[ ( TSK_BGKND_STACK_SIZE ) / sizeof( uint16 ) ];

/* current stack pointer */
static volatile void * volatile stack_ptr;

// TODO make work with more than one task
static tcb_t * next_task;

/*---------------------------------------
Variables
----------------------------------------*/
static list_t * s_task_list;

/*---------------------------------------
Procedures
----------------------------------------*/
static err_t insert_new_task(tcb_t * tcb);
static void TSK_background(void);
static tcb_t * get_next_task();


void TSK_scheduler(void)
{


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
    // TODO update task starting procedures 
    task_init();

    /* configure timer */
	TB0CTL |= TBCLR;             /* clear timer on start (recomended) */
	TB0CTL |= MC__CONTINUOUS;    /* set as cont mode */
	TB0CTL |= TBSSEL__ACLK;      /* set clock as ACLK */
	TB0CTL |= TBIE;              /* set local enable for timer */

    return NO_ERR;
}

/*---------------------------------------
 task_init()

 start the task scheduler
----------------------------------------*/
err_t task_init()
{
    /* create background task */
    tcb_t tsk_bkgnd;

    tsk_bkgnd.task_proc = TSK_background;
    tsk_bkgnd.name = "Background Task";

    /* initialize stack ptr */
    tsk_bkgnd.stack = tsk_bkgn_stack;

    task_add(&tsk_bkgnd);

    return NO_ERR;
}

err_t task_add(tcb_t * tcb)
{
    /* local variables */
    uint8 i = 0;

    /* set up the stack for this task */

                    /* store bits 15:0 for the program counter */
    *( --(tcb->stack)) = (uint16)tcb->task_proc;

                    /*  store Global Interrupt Enable Bit
                        
                        Note that the program counter 19:16
                        are also stored here but will be 0
                        at this time since only using small
                        memory model
                    */
    *( --(tcb->stack)) = GIE;

    /* clear registers 4 through 15 */
    for(i = 4; i < 16; i++)
    {
        *( --(tcb->stack)) = 0;
        *( --(tcb->stack)) = 0;

    }

    // TODO make work with more than one task
    next_task = tcb;

    /* update the task stack pointer */

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

static void TSK_background(void)
{
    /*  just blink led for now to show that this
        procedure is being called
    */
    toggle_led();

    while(1)
    {}
}

/* 
    timer_intr_hndlr()

    Description:
    Main timer interrupt handler

    Note:
    At this time, the main job of this procedure
    is to call the task scheduler
*/

__attribute__((interrupt(TIMER0_B1_VECTOR)))
void timer_intr_hndlr(void)
{
    /*  current task to execute */
    static volatile tcb_t * volatile tcb_ptr = NULL;

    //TODO  ensure compiler does not optimize here by
    //TODO  by adding to the stack. Should have complete
    //TODO  control over the stack at this time

        /* move registers 4 through 15 onto the stack */
    asm (" pushm.a #12, r15 \n\t");

        /* save the stack pointer in tcb stack ptr reference */
    asm (" mov sp,  stack_ptr \n\t");

    /*  if a task has been loaded in the scheduler
        then save the reference to current task
        stack pointer
    */    
    if( tcb_ptr != NULL )
    {
        tcb_ptr->stack = stack_ptr;
    }

    /* update current running task to get in queue */
    tcb_ptr = get_next_task();
    
    /* update the stack pointer */
    stack_ptr = tcb_ptr->stack;
    asm (" mov stack_ptr, sp \n\t");

    /* restore general purpose registers */
    asm (" popm.a #12, r15 \n\t");

    /*  return from interrupt which will "restore" previous state 
        which has since been altered by stack manipulation 
    */
    asm (" RETI \n\t");

}

static tcb_t * get_next_task()
{
    return next_task; // TODO   make work with more than one task
}