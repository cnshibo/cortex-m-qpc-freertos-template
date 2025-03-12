#include "bl/delay.h"
#include "bl/common.h"
#include "arm_acle.h"

//resolution: 20ns
void delay_cycle(uint32_t time)
{
    uint32_t i;

    for(i=0;i<time;i++)
    {
        __nop();
    }
}

void delay_us(uint32_t time)
{
    uint32_t i,j;

    for(i=0;i<time;i++)
    {
        for(j=0;j<48;j++)
        {
         __nop();
        }
    }
}

void delay_ms(uint32_t time)
{
    uint32_t i;

    for(i=0;i<time-1;i++)
    {
        delay_us(1000);
    }
}
