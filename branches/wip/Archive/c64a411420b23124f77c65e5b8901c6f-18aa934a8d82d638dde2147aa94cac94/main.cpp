#include <iostream>
#include <utility>


template<typename T, typename U>
constexpr int foo(std::pair<T, U> p)
{
    return p.first < 10 ? foo(std::make_pair(p.first+1, p.second+2)) : p.first + p.second;
}


int main()
{
    enum {
        result = foo(std::make_pair(0, 0))
    };
    std::cout << result << std::endl;
}