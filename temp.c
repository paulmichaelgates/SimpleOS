#include <msp430.h> 
#include "msp430fr2355.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	 // stop watchdog timer

	// set up led output p1.0
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;              // clear on init
	
	// enable digital I/O
	PM5CTL0   &= ~LOCKLPM5;

	// set up timer b0
	TB0CTL |= TBCLR;             // clear timer on start (recomended)
	TB0CTL |= MC__CONTINUOUS;    // set as cont mode
	TB0CTL |= TBSSEL__ACLK;      // set clock as ACLK
	TB0CTL |= TBIE;              // set local enable for timer

	__enable_interrupt();        // enable global interrupt

    TB0CTL &= ~TBIFG;            // clear ifg (recomended)

	// main loop
	while(1);

	return 0;
}

__attribute__((interrupt(TIMER0_B1_VECTOR)))
void toggle_led(void){
    P1OUT ^= BIT0;               // toggle led
    TB0CTL &= ~TBIFG;            // clear ifg
}

