/**
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */
#ifndef ESTD_UNCOPYABLE_H
#define ESTD_UNCOPYABLE_H

#define UNCOPYABLE(T)   \
    T(const T&);        \
    T& operator=(const T&)

#endif
