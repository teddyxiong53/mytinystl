#ifndef _TINYSTL_BUFFER_H_
#define _TINYSTL_BUFFER_H_

#include "allocator.h"
#include "new.h"
#include "traits.h"

namespace tinystl
{
template<typename T, typename Alloc = TINYSTL_ALLOCATOR>
struct buffer {
    T* first;
    T* last;
    T* capacity;
};

template<typename T, typename Alloc>
static inline void buffer_init(buffer<T, Alloc> *b)
{
    b->first = b->last = b->capacity = 0;
}

} // namespace tinystl

#endif