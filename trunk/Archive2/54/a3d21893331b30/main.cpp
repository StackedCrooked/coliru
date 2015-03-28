#include <boost/pool/pool_alloc.hpp>
#include <vector>
#include <iostream>


template<typename T>
struct Alloc : boost::fast_pool_allocator<T>
{
    using base = boost::fast_pool_allocator<T>;
    using pointer = typename base::pointer;
    using size_type = typename base::size_type;

    pointer allocate(const size_type n)
    {
        std::cout << " +" << n;
        return base::allocate(n);
    }

    void deallocate(pointer ptr, size_type n)
    {
        std::cout << " -" << n;
        return base::deallocate(ptr, n);
    }
};


int main()
{
    std::vector<int, Alloc<int>> vec;

    for (int i = 0; i < 100; ++i)
    {
        vec.push_back(i);
    }
}
