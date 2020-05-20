#ifndef _TINYSTL_VECTOR_H_
#define _TINYSTL_VECTOR_H_
#include "allocator.h"
#include "buffer.h"
#include "new.h"
#include "stddef.h"

namespace tinystl
{
template<typename T, typename Alloc = TINYSTL_ALLOCATOR>
class vector {
public:
    vector();
    vector(const vector& other);
    vector(const vector&& other);
private:
    buffer<T, Alloc> m_buffer;

};
template<typename T, typename Alloc>
inline vector<T, Alloc>::vector()
{
    buffer_init(&m_buffer);
}
} // namespace tinystl

#endif