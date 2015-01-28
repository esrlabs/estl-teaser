#ifndef estd_config_h
#define estd_config_h

/*
 * Include compiler and OS specific checks.
 */
#ifdef __GNUC__
#  include <estd/config/gnu.h>
#endif

#ifdef __DCC__
#  include <estd/config/diab.h>
#endif

#define ESTD_EXCEPTION_LIKE_CALLBACKS 1

#endif
