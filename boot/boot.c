
/* TI includes */
#include <msp430.h> 
#include "msp430fr2355.h"

/* Project includes */
#include "watchdog_intf.h"
#include "task_schedule.h"
#include "io_intf.h"

/*---------------------------------------
 Procedures
----------------------------------------*/

static void enable_interrupts(void);

/**
 * main.c
 */
int main(void)
{
	disable_watchdog();

	// set up led output p1.0
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;              // clear on init
	
    io_bootup();

    enable_interrupts();

    task_bootup_sched();

	// main loop
	while(1);

	return 0;
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

