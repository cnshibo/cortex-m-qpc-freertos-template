#ifndef __Bl_MEMMEM_H__
#define __Bl_MEMMEM_H__

#include "bl/types.h"

PN_BEGIN_DECL

void *memmem(const void *l, size_t l_len, const void *s, size_t s_len);

PN_END_DECL
#endif
