#include "dl/time.h"
#include "dl/vendor.h"
#include "bl/bl.h"

typedef struct time_clock_t
{
    uint32_t ticks; // milliseconds

    uint32_t systick_load;
} time_clock_t;

static time_clock_t l_time;

void time_init(void)
{
    l_time.ticks = 0;
    l_time.systick_load = SysTick->LOAD + 1;
}

void time_increase_tick(void)
{
    l_time.ticks++;
}

uint32_t time_get_elapsed_ms(void)
{
    return l_time.ticks;
}

uint32_t time_get_elapsed_us(void)
{
    __IO uint32_t systick_value = SysTick->VAL;

    return (l_time.ticks * 1000 + (l_time.systick_load - systick_value) * 1000 / l_time.systick_load);
}

/************************************************************************/

/************************************************************************/
void test_time(void)
{
    int32_t t1 = time_get_elapsed_us();
    LOG("%d ", t1);

    int32_t t2 = time_get_elapsed_us();
    time_get_elapsed_us();
    time_get_elapsed_us();
    time_get_elapsed_us();
    time_get_elapsed_us();
    time_get_elapsed_us();
    time_get_elapsed_us();
    t2 = time_get_elapsed_us();

    LOG("%d %d", t1, t2);
}