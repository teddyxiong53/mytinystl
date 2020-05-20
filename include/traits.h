#ifndef _TINYSTL_TRAINTS_H_
#define _TINYSTL_TRAINTS_H_

#include "new.h"

#define TINYSTL_TRY_POD_OPTIMIZATION(t) false
namespace tinystl
{
template<typename T, bool pod = TINYSTL_TRY_POD_OPTIMIZATION(T)>
struct pod_traits {

};
template<typename T, T t>
struct swap_holder;

template <typename T>
static inline void move_impl(T& a, T& b, ...)
{
    a = b;
}

template<typename T>
static inline void move_impl(T& a, T& b, swap_holder<void (T::*)(T&), &T::swap>* = 0)
{
    a.swap(b);
}

template<typename T>
static inline void move(T& a, T& b)
{
    move_impl(a, b, (T*)0);
}

template<typename T>
static inline void move_construct_impl(T* a, T& b, ...)
{
    new(placeholder(), a) T(b);
}

template<typename T>
static inline void move_construct_impl(T* a, T& b, swap_holder<void (T::*)(T&), &T::swap>* = 0)
{
    new(placeholder(), a) T;
    a->swap(b);
}

template<typename T>
static inline void move_construct_impl(T* a, T& b, T*, typename T::tinystl_nomove_construct* = 0)
{
    new(placeholder(), a) T(b);
}
template<typename T>
static inline void move_construct(T* a, T& b)
{
    move_construct_impl(a, b, (T*)0);
}

template<typename T>
struct remove_reference {
    typedef T type;
};

template<typename T>
struct remove_reference<T&> {
    typedef T type;
};

template<typename T>
struct remove_reference<T&&> {
    typedef T type;
};


} // namespace tinystl



#endif