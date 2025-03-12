#ifndef  __BL_LOG_H__
#define  __BL_LOG_H__

#include <stdio.h>
#include "SEGGER_RTT.h"
#include "bl/types.h"

PN_BEGIN_DECL

#define __DEBUG__

#ifdef __DEBUG__
#define LOG(format, ...) printf(format "\n", ##__VA_ARGS__)
// #define LOG(format, ...) SEGGER_RTT_printf(0, format"\n\r", ##__VA_ARGS__);
#else
#define LOG(format, ...)
#endif

PN_END_DECL
#endif
