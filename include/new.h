#ifndef _TINYSTL_NEW_H_
#define _TINYSTL_NEW_H_

#include "stddef.h"

namespace tinystl
{
struct placeholder {

};

} // namespace tinystl
inline void *operator new(size_t, tinystl::placeholder, void *ptr) {
    return ptr;
}

inline void operator delete(void *, tinystl::placeholder, void *) throw() {

}
#endif