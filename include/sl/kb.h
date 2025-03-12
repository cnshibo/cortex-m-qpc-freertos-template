#ifndef __SL_KB_H__
#define __SL_KB_H__

#include "bl/types.h"

PN_BEGIN_DECL

void kb_init(void);
void kb_scan(void);
void kb_dispatch_event(uint8_t id, uint8_t state);

PN_END_DECL

#endif
