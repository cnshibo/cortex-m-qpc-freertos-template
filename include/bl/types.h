#ifndef __BL_TYPES_H__
#define __BL_TYPES_H__

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "bl/config.h"
#include "bl/errno.h"

#ifdef __cplusplus
#define PN_BEGIN_DECL extern "C" {
#define PN_END_DECL }
#else
#define PN_BEGIN_DECL
#define PN_END_DECL
#endif

/** status code. */
typedef int pn_status_t;

/** Some constants */
enum pn_constants_
{
    /** Status is OK. */
    PN_SUCCESS = 0,

    /** True value. */
    PN_TRUE = 1,

    /** False value. */
    PN_FALSE = 0
};

typedef struct pn_str_t
{
    /** Buffer pointer, which is by convention NOT null terminated. */
    uint8_t *ptr;

    /** The length of the string. */
    uint32_t slen;
} pn_str_t;

#endif /* __PN_TYPES_H__ */
