/*

watchdog_intf.h

Description: 
    Provides declarations for public procedures for the
    watchdog timer

*/
#ifndef WATCHDOG_INTF_H
#define WATCHDOG_INTF_H

/*---------------------------------------
Includes
----------------------------------------*/
#include "msp430.h"
#include "msp430fr2355.h"

/*---------------------------------------
 disable_watchdog()
----------------------------------------*/
__inline void disable_watchdog (void)
{
    WDTCTL = WDTPW | WDTHOLD;
}

#endif /* WATCHDOG_INTF_H */