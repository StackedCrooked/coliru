#include <utility>
#include <iostream>

template <class T>
void foo(const T& v)
{
    std::cout << "Generic version" << std::endl;
}

void foo(std::pair<const void*, std::size_t> p)
{
    std::cout << "Pair version" << std::endl;
}

int main()
{
    const void* buf = 0;
    std::size_t sz = 0;
    foo(std::make_pair(buf, sz));
}

