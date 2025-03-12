/******************************************************************************/
/* RETARGET.C: 'Retarget' layer for target-dependent low level functions      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005 Keil Software. All rights reserved.                     */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

/*
 * https://mklimenko.github.io/english/2018/11/02/disable-semihosting/
 * https://developer.arm.com/documentation/dui0475/c/the-arm-c-and-c---libraries/using-the-libraries-in-a-nonsemihosting-environment
 * https://developer.arm.com/documentation/ka002219/latest
 * https://www.keil.com/pack/doc/compiler/RetargetIO/html/_retarget__overview.html
*/

#include <stdio.h>
#include <time.h>
#include <rt_misc.h>

#include "SEGGER_RTT.h"

__asm(".global __use_no_semihosting_swi");

FILE __stdout;
FILE __stdin;

// for jlink rtt
int fputc(int ch, FILE *f)
{
    SEGGER_RTT_PutChar(0, ch);

    return (ch);
}

int fgetc(FILE *f)
{
    return SEGGER_RTT_GetKey();
}

int ferror(FILE *f)
{
    /* Your implementation of ferror */
    return EOF;
}

void _ttywrch(int ch)
{
    
}

void _sys_exit(int return_code)
{
    while (1)
        ; /* endless loop */
}
