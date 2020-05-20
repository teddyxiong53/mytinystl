#ifndef _TINYSTL_ALLOCATOR_H_
#define _TINYSTL_ALLOCATOR_H_

#include "stddef.h"
namespace tinystl
{
struct allocator {
    static void *static_allocate(size_t bytes) {
        return operator new(bytes);
    }
    static void static_deallocate(void *ptr, size_t bytes) {
        operator delete(ptr);
    }
};
#define TINYSTL_ALLOCATOR ::tinystl::allocator

} // namespace tinystl

#endif