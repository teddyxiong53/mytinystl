#ifndef _TINYSTL_HASH_H_
#define _TINYSTL_HASH_H_
#include "stddef.h"

namespace tinystl
{
static inline size_t hash_string(const char *str, size_t len) {
    size_t hash = 0;
    typedef const char * pointer;
    for(pointer it = str, end = str + len; it !=end; ++it) {
        hash = *it + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}
template <typename T>
inline size_t hash(const T& value) {
    const size_t asint = (size_t)value;
    return hash_string((const char *)&asint, sizeof(asint));
}
} // namespace tinystl

#endif