#ifndef _TINYSTL_STRING_H_
#define _TINYSTL_STRING_H_

#include "allocator.h"
#include "hash.h"

namespace tinystl
{
template <typename Allocator>
class basic_string {
public:
    basic_string();
    basic_string(const basic_string& other);
    basic_string(basic_string&& other);
    basic_string(const char *sz);
    basic_string(const char *sz, size_t len);
    ~basic_string();

    basic_string& operator=(const basic_string& other);
    basic_string& operator=(basic_string&& other);

    const char *c_str() const;
    size_t size() const;

    void reserve(size_t size);
    void resize(size_t size);

    void clear();
    void append(const char *first, const char *last);
    void assign(const char *s, size_t n);

    void shrink_to_fit();
    void swap(basic_string& other);
private:
    typedef char *pointer;
    pointer m_first;
    pointer m_last;
    pointer m_capacity;

    static const size_t c_nbuffer = 12;
    char m_buffer[12];

};


template<typename allocator>
inline void basic_string<allocator>::clear()
{
    resize(0);
}

template<typename allocator>
inline void basic_string<allocator>::assign(const char *sz, size_t n)
{
    clear();
    append(sz, sz+n);
}

template<typename allocator>
static inline size_t hash(const basic_string<allocator>& value)
{
    return hash_string(value.c_str(), value.size());
}
template<typename allocator>
inline basic_string<allocator>::~basic_string()
{
    if(m_first != m_buffer) {
        allocator::static_deallocate(m_first, m_capacity - m_first);
    }
}

template<typename allocator>
inline void basic_string<allocator>::append(const char *first, const char *last)
{
    const size_t newsize = (size_t)( (m_last - m_first) + (last - first) + 1 );
    if(m_first + newsize > m_capacity) {
        reserve((newsize*3)/2);
    }
    for(; first!=last; ++m_last, ++first) {
        *m_last = *first;
    }
    *m_last= 0;
}

template<typename allocator>
inline basic_string<allocator>::basic_string(const char *sz)
 : m_first(m_buffer),
   m_last(m_buffer),
   m_capacity(m_buffer + c_nbuffer)
{
    size_t len = 0;
    for(const char *it = sz; *it; ++it) {
        ++len;
    }
    reserve(len);
    append(sz, sz+len);

}
template <typename allocator>
inline void basic_string<allocator>::reserve(size_t capacity)
{
    if(m_first + capacity + 1 <= m_capacity) {
        return;
    }
    const size_t size = (size_t)(m_last - m_first);
    pointer newfirst = (pointer)allocator::static_allocate(capacity+1);

    for(pointer it=m_first, newit=newfirst, end=m_last;
        it != end;
        ++it, ++newit)
    {
        *newit = *it;
    }
    if(m_first != m_buffer) {
        allocator::static_deallocate(m_first, m_capacity - m_first);
    }
    m_first = newfirst;
    m_last = newfirst + size;
    m_capacity = m_first + capacity;
}

template<typename allocator>
inline void basic_string<allocator>::resize(size_t size)
{
    const size_t prevSize = m_last - m_first;
    reserve(size);
    if(size > prevSize) {
        for(pointer it=m_last, end=m_first + size+1;
            it < end; ++it)
        {
            *it = 0;
        }
    } else if(m_last != m_first) {
        m_first[size] = 0;
    }
    m_last = m_first + size;
}
template<typename allocator>
inline basic_string<allocator>::basic_string()
 : m_first(m_buffer),
   m_last(m_buffer),
   m_capacity(m_buffer + c_nbuffer)
{
    resize(0);
}
template <typename allocator>
inline size_t basic_string<allocator>::size() const
{
    return (size_t)(m_last - m_first);
}

template<typename allocator>
inline basic_string<allocator>::basic_string(const basic_string& other)
 : m_first(m_buffer),
   m_last(m_buffer),
   m_capacity(m_buffer+c_nbuffer)
{
    reserve(other.size());
    append(other.m_first, other.m_last);
}

template<typename allocator>
inline basic_string<allocator>::basic_string(const char *sz, size_t len)
 : m_first(m_buffer),
   m_last(m_buffer),
   m_capacity(m_buffer + c_nbuffer)
{
    reserve(len);
    append(sz, sz+len);
}
template<typename allocator>
inline basic_string<allocator>::basic_string(basic_string&& other)
{
    if(other.m_first == other.m_buffer) {
        m_first = m_buffer;
        m_last = m_buffer;
        m_capacity = m_buffer + c_nbuffer;
        reserve(other.size());
        append(other.m_first, other.m_last);
    } else {
        m_first = other.m_first;
        m_last = other.m_last;
        m_capacity = other.m_capacity;
    }
    other.m_first = other.m_last = other.m_buffer;
    other.m_capacity = other.m_buffer + c_nbuffer;
    other.resize(0);
}

template<typename allocator>
inline basic_string<allocator>& basic_string<allocator>::operator=(const basic_string& other)
{
    basic_string(other).swap(*this);
    return *this;
}

template<typename allocator>
inline  basic_string<allocator>& basic_string<allocator>::operator=(basic_string&& other)
{
    basic_string(static_cast<basic_string&&>(other)).swap(*this);
    return *this;
}

template <typename allocator>
inline void basic_string<allocator>::swap(basic_string& other)
{
    const pointer tfirst = m_first, tlast = m_last, tcapacity = m_capacity;
    m_first = other.m_first;
    m_last = other.m_last;
    m_capacity = other.m_capacity;

    other.m_first = tfirst;
    other.m_last = tlast;
    other.m_capacity = tcapacity;

    char tbuffer[c_nbuffer];

    if(m_first == other.m_buffer) {
        for(pointer it=other.m_buffer, end = m_last, out=tbuffer;
            it !=end;
            ++it, ++out)
        {
            *out = *it;
        }

    }
    if(other.m_first == m_buffer) {
        other.m_last = other.m_last - other.m_first + other.m_buffer;
        other.m_first = other.m_buffer;
        other.m_capacity = other.m_buffer + c_nbuffer;

        for(pointer it=other.m_first, end=other.m_last, in=m_buffer;
            it != end;
            ++it, ++in)
        {
            *it = *in;
        }
        other.m_last = 0;
    }
    if(m_first == other.m_buffer) {
        m_last = m_last - m_first + m_buffer;
        m_first = m_buffer;
        m_capacity = m_buffer + c_nbuffer;

        for(pointer it=m_first, end=m_last, in=tbuffer;
            it != end;
            ++it, ++in)
        {
            *it = *in;
        }
        *m_last = 0;
    }

}

template<typename allocator>
inline const char * basic_string<allocator>::c_str() const
{
    return m_first;
}

typedef basic_string<TINYSTL_ALLOCATOR> string;

} // namespace tinystl


#endif