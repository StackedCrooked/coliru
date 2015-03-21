#include <iostream>

template<typename T>
struct tag
{
    using type = T;
};

template<typename U>
using type = typename U::type;

int main()
{
    auto l = [] (auto x) 
    { 
        using T = type<decltype(x)>; 
        auto y = T{}; 
        std::cout << y;
    };
    
    l(tag<int>{});
}

