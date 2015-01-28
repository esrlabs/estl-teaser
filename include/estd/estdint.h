/**
 * Contains typedefs for standard types if compiler does not support them.
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */
#ifndef ESTD_ESTDINT_H
#define ESTD_ESTDINT_H

#include <estd/config.h>

#ifdef HAS_STDINT_H_
#  include <stdint.h>
#endif

#ifdef HAS_CSTDINT_H_
#  include <cstdint>
#endif

#endif
