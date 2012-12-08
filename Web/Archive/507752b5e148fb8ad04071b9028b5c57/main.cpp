#include <iostream>
#include <vector>


template<typename T, template<class, class...> class Alloc = std::allocator, class ...AllocArgs>
struct Vector : Alloc<T, AllocArgs...>
{
};


int main()
{    
    Vector<int>();
    Vector<int, std::allocator>();
}