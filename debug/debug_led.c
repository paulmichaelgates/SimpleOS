/* 
    debug_led.c

    Description:
    provides procedures for messing with debug leds.
    
    Notes:
    For now there is just a single output to main led
    which toggles everytime the task scheduler is called
    but eventually there will be different configurations
    that can be used to indicate certain software states
    that will make debugging easier
*/

#include <msp430.h>
#include "msp430fr2355.h"

void toggle_led()
{
    P1OUT ^= BIT0;               // toggle led
}