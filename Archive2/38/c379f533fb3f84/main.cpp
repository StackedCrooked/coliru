#include <stdexcept>
#include <iostream>

template<class T>
constexpr auto foo(T const& t) noexcept
{
    return t;
}

template<class T>
constexpr auto bar(T const& t)
{
    switch (foo(t)) {
    case 0: return t;
    default: return throw std::logic_error("can only handle zero values");    
    }
}

int main()
{
    //auto constexpr f = foo(0);
    //std::cout << f << "\n";
    std::cout << "Hello world\n";
}