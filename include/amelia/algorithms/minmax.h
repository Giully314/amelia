// amelia/minmax.h
// PURPOSE: Define min and max utility functions.

#ifndef _AMELIA_MINMAX_H
#define _AMELIA_MINMAX_H

#include <amelia/basic_types.h>


static inline i64 min(i64 a, i64 b) {
    return a < b ? a : b;
}

static inline i64 max(i64 a, i64 b) {
    return a > b ? a : b;
}

#endif // _AMELIA_MINMAX_H