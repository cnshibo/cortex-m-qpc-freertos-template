#ifndef __DL_TIME_H__
#define __DL_TIME_H__

#include "bl/types.h"

PN_BEGIN_DECL

typedef struct timestamp_t
{
    uint32_t milliseconds; // ms
    uint32_t microseconds; // us
} timestamp_t;


void time_init(void);
void time_increase_tick(void);

void time_get_timestamp(timestamp_t *ts);

uint32_t time_get_elapsed_ms(void);
uint32_t time_get_elapsed_us(void);

uint32_t time_elapsed_ms(timestamp_t *start, timestamp_t *stop);
uint32_t time_elapsed_us(timestamp_t *start, timestamp_t *stop);

void test_time(void);

PN_END_DECL
#endif //__BL_TIME_H__
