#include <iostream>
#include <type_traits>
#include <cstring>

auto ptr_memset =  std::memset; //store this a pointer

#define memset memset_if_pod_else_error

template<typename T>
auto memset_if_pod_else_error(T *data, int ch, size_t count) -> typename std::enable_if<std::is_pod<T>::value, void*>::type
{
      return ptr_memset(data, ch, count);
}


struct pod {};
struct nonpod { nonpod() {} };

int main()
{
    pod p;
    nonpod np;
    
    memset(&p, 0, sizeof(p));
    
    memset(&np, 0, sizeof(np));
}
