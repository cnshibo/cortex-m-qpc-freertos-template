#include "bl/rtt.h"
#include "SEGGER_RTT.h"
#include "bl/log.h"


void rtt_init(void)
{
    //
}

void rtt_print_menu(void)
{
    SEGGER_RTT_WriteString(0, "SEGGER Real-Time-Terminal Sample\r\n");
}

/* poll down channel buffer */
void rtt_poll(void)
{
    int r = SEGGER_RTT_GetKey();

    if (r >= 0)
    {
        switch (r)
        {
        case 'a':
            //
            LOG("rx a");
            break;
        case 'e':
            
            break;

        default:
            //unknow commnand
            break;
        }
    }
    else
    {
        //no input
    }
}