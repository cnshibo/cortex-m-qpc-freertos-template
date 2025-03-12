#ifndef __BL_ERRNO_H__
#define __BL_ERRNO_H__

/**
 * PN_ERRNO_START is where PNLIB specific error values start.
 */
#define PN_ERRNO_START 20000

/**
 * PN_ERRNO_SPACE_SIZE is the maximum number of errors in one of
 * the error/status range below.
 */
#define PN_ERRNO_SPACE_SIZE 50000

/**
 * PN_ERRNO_START_STATUS is where PJLIB specific status codes start.
 * Effectively the error in this class would be 70000 - 119000.
 */
#define PN_ERRNO_START_STATUS (PN_ERRNO_START + PN_ERRNO_SPACE_SIZE)

/**
 * PN_ERRNO_START_SYS converts platform specific error codes into
 * PN_status_t values.
 * Effectively the error in this class would be 120000 - 169000.
 */
#define PN_ERRNO_START_SYS (PN_ERRNO_START_STATUS + PN_ERRNO_SPACE_SIZE)

/**
 * PN_ERRNO_START_USER are reserved for applications that use error
 * codes along with PJLIB codes.
 * Effectively the error in this class would be 170000 - 219000.
 */
#define PN_ERRNO_START_USER (PN_ERRNO_START_SYS + PN_ERRNO_SPACE_SIZE)

/************************************************************************/

#define PN_EUNKNOWN (PN_ERRNO_START_STATUS + 1) /* 70001 */
/**
 * @hideinitializer
 * The operation is pending and will be completed later.
 */
#define PN_EPENDING (PN_ERRNO_START_STATUS + 2) /* 70002 */

/**
 * @hideinitializer
 * Need to be called again
 */
#define PN_EAGAIN (PN_ERRNO_START_STATUS + 4)

/**
 * @hideinitializer
 * Invalid argument.
 */
#define PN_EINVAL (PN_ERRNO_START_STATUS + 5)

/**
 * @hideinitializer
 * Not found.
 */
#define PN_ENOTFOUND (PN_ERRNO_START_STATUS + 6)

/**
 * @hideinitializer
 * Not enough memory.
 */
#define PN_ENOMEM (PN_ERRNO_START_STATUS + 8)

#endif
