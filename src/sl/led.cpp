#include "sl/led.h"
#include "dl/common.h"
#include "dl/stm.h"

void led_init(void)
{

}

void led_switch(bool on)
{
    if (on)
    {

        //PF4 = 1;
        LL_GPIO_SetOutputPin(LED_0_GPIO_Port, LED_0_Pin);
    }
    else
    {

        //PF4 = 0;
        LL_GPIO_ResetOutputPin(LED_0_GPIO_Port, LED_0_Pin);
    }
}
