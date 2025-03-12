#include "dl/dl_cpu.h"
#include "dl/dl_common.h"

void cpu_reset()
{
    NVIC_SystemReset();
}
