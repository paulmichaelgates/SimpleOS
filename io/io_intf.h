/*

io_intf.h

*/
#ifndef IO_INTF_H
#define IO_INTF_H


/*---------------------------------------
 Includes
----------------------------------------*/

/* TI includes */
#include <msp430.h> 
#include "msp430fr2355.h"

__inline void io_bootup()
{
	/* enable digital I/O */
	PM5CTL0   &= ~LOCKLPM5;
}

#endif /* IO_INTF_H */