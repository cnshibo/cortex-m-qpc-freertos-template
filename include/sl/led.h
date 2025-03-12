#ifndef __DL_LED_H__
#define __DL_LED_H__

#include "bl/types.h"

PN_BEGIN_DECL

void led_init(void);
void led_switch(bool on);

PN_END_DECL
#endif
