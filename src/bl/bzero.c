#include "bl/bzero.h"

void bzero(void *const start, uint16_t const len)
{
    uint8_t *ptr = (uint8_t *)start;
    for (uint16_t n = len; n > 0U; --n)
    {
        *ptr = 0U;
        ++ptr;
    }
}
