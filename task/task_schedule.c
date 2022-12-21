/* Copyright (c) 2014, Jeffrey Antony     */
/* Read license file for more information */

#include <msp430.h>
#include "msp430fr2355.h"
#include "utl_simple.h"
#include "debug.h"
#include "io_intf.h"

#define BACKUP_REGS 12 /* r4 to r15*/

#define STACK_SIZE 64
#define STACK_TOP   STACK_SIZE - 1   
#define TOTAL_TASKS 1

/*Enable GIE in SR so that the WDT never stops when we go to user task*/
/*Enable SCG0 for 25MHZ CPU execution*/
#define DEFAULT_SR  ((uint16_t)0x0048) 

#define SAVE_CONTEXT()           \
  asm volatile ( "push r4  \n\t" \
                 "push r5  \n\t" \
                 "push r6  \n\t" \
                 "push r7  \n\t" \
                 "push r8  \n\t" \
                 "push r9  \n\t" \
                 "push r10 \n\t" \
                 "push r11 \n\t" \
                 "push r12 \n\t" \
                 "push r13 \n\t" \
                 "push r14 \n\t" \
                 "push r15 \n\t" \
               );

#define RESTORE_CONTEXT()       \
  asm volatile ( "pop r15 \n\t" \
                 "pop r14 \n\t" \
                 "pop r13 \n\t" \
                 "pop r12 \n\t" \
                 "pop r11 \n\t" \
                 "pop r10 \n\t" \
                 "pop r9  \n\t" \
                 "pop r8  \n\t" \
                 "pop r7  \n\t" \
                 "pop r6  \n\t" \
                 "pop r5  \n\t" \
                 "pop r4  \n\t" \
                 "reti    \n\t" \
               );


uint16_t task1ram[STACK_SIZE];
//uint16_t task2ram[STACK_SIZE];
//uint16_t task3ram[STACK_SIZE];

volatile uint8_t  task_id; /*has the current running task*/
volatile uint16_t *stack_pointer[TOTAL_TASKS]; /*address of stack pointer for each task*/

void task1(void)
{ 
    P1OUT ^= BIT0;               // toggle led


}

void task2(void)
{
   

}

void task3(void)
{
   
}


/*****************************************************/

/*
 * This function will initialise stack for each task. Following are filled into the stack
 * 1) Store the PC first since it has to be poped back and loaded at end 
 * 2) then store SR register. This determines the CPU condition at which your task should execute
 * 3) leave the space for the registers r4 to r15 since the scheduler will pop these when a task switching occurs
 * 3) return the address of stack which will contain all informations for the task to execute after task switching
 * 4) TODO: fill the end of stack with known values to detect buffer overflows.
 */
uint16_t *initialise_stack(void (* func)(void), uint16_t *stack_location)
{
  uint8_t i;
  
  /*MSP430F5529 has a 20bit PC register*/
  *stack_location = (uint16_t)func; //last 16 bits will only stored. Pending 4bits will be stored with SR
  stack_location--;
  /*refer datasheet to see how 20bit PC is stored along with SR*/
  *stack_location = (((uint16_t)((uint32_t)(0xf0000 & (uint32_t)func) >> 4))| DEFAULT_SR); //TODO:fix compiler warning
  
  /*leave space in stack for r4 to r15*/
  for(i= 0; i< BACKUP_REGS; i++)
  {
    stack_location--;
  }
  
  /*TODO: fill bottom of stack to detect buffer overflow*/
  
  return stack_location;
}


/*---------------------------------------
 task_bootup_sched()

boot up procedure for the task scheduler
----------------------------------------*/
err_t task_bootup_sched()
{
    // Worst-case settling time for the DCO when the DCO range bits have been
    // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
    // UG for optimization.
    // 32 x 32 x 25 MHz / 32,768 Hz ~ 780k MCLK cycles for DCO to settle
    __delay_cycles(782000);

    /* configure timer */
	TB0CTL |= TBCLR;             /* clear timer on start (recomended) */
	TB0CTL |= MC__CONTINUOUS;    /* set as cont mode */
	TB0CTL |= TBSSEL__ACLK;      /* set clock as ACLK */
	TB0CTL |= TBIE;              /* set local enable for timer */

    return NO_ERR;

}

static volatile uint16_t *temp;

void main(void)
{

    // set up led output p1.0
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;              // clear on init

    io_bootup();

	// __enable_interrupt();        /* enable global interrupts */

    // TB0CTL &= ~TBIFG;            // clear ifg (recomended)

    //Stop the watchdog timer until we configure our scheduler
    WDTCTL = WDTPW + WDTHOLD;

    /*initialise stack for each task*/
    stack_pointer[0] = initialise_stack(task1, &task1ram[STACK_TOP]);
    //stack_pointer[1] = initialise_stack(task2, &task2ram[STACK_TOP]);
    //stack_pointer[2] = initialise_stack(task3, &task3ram[STACK_TOP]);
    
    task_bootup_sched();

    /*initialise to first task*/
    task_id =0;
    
    //set the stack pointer to task1's RAM location
    temp = stack_pointer[task_id];
    asm volatile ("mov.w temp, r1 \n\t");
    
    // lets pop our first task out!  
    RESTORE_CONTEXT();
}


__attribute__((interrupt(TIMER0_B1_VECTOR)))
void timer_intr_hndlr(void){

    
    SAVE_CONTEXT(); /*save current registers into stack. PC and SR will be saved automatically when an interrupt occurs*/
    
    //if required, we can stop the WDT here until we are done with all the works for context switching.
    //then start the WDT before restoring the context (this step is not required since our SR is by default is enabled with global interrupts)
    //we can do a stack overflow check here
    
    /*backup the stack pointer*/
    asm volatile ("mov.w r1, temp \n\t");
    stack_pointer[task_id] = temp;
    
    //round robin scheduling
    if(task_id < (TOTAL_TASKS-1))
    {
        task_id++;
    }
    else
    {
        task_id = 0;
    }

    /*check for stack overflow*/
    
    temp = stack_pointer[task_id];
    asm (  "mov.w  temp, r1    \n\t");

    RESTORE_CONTEXT();

}