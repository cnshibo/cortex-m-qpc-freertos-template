#ifndef __SL_GPIO_H__
#define __SL_GPIO_H__

#include "bl/types.h"

PN_BEGIN_DECL

void gpio_init(void);

void gpio_test_pin(bool on);

PN_END_DECL

#endif