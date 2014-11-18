#ifndef ESTD_UNCOPYABLE_H
#define ESTD_UNCOPYABLE_H

#define UNCOPYABLE(T)   \
    T(const T&);        \
    T& operator=(const T&)

#endif
