
/* TI includes */
#include <msp430.h> 
#include "msp430fr2355.h"

/* Project includes */
#include "watchdog_intf.h"
#include "task_schedule.h"
#include "io_intf.h"

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

    task_bootup_sched();

	// main loop
	while(1);

	return 0;
}

__attribute__((interrupt(TIMER0_B1_VECTOR)))
void toggle_led(void){
    P1OUT ^= BIT0;               // toggle led
    TB0CTL &= ~TBIFG;            // clear ifg
}

