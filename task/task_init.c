/* 
    task_init.c

    Description

        handles taks type definitions from the user.
        Tasks are created by the user using a task
        task definition type and then use task_init
        to initialize them
*/

/*---------------------------------------
 Includes
----------------------------------------*/
#include <msp430.h>
#include "msp430fr2355.h"

#include "utl_types.h"

/*---------------------------------------
 Literal contants
----------------------------------------*/

/*---------------------------------------
 Procedures
----------------------------------------*/
static void enable_interrupts(void);

/*---------------------------------------
 task_init()

 insert a task into the task linked list
----------------------------------------*/
err_t task_init()
{
    return NO_ERR;
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

    enable_interrupts();

    return NO_ERR;
}

/*---------------------------------------
 enable_interrupts()

enable hardware interrupts
----------------------------------------*/

static void enable_interrupts(void)
{
	__enable_interrupt();        /* enable global interrupts */

    TB0CTL &= ~TBIFG;            // clear ifg (recomended)
}
