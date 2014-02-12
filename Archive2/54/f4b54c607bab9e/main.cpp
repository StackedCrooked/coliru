#include <iostream>
#include <cmath>
#include <type_traits>

template <typename T, typename Ret = T>
Ret xround(T val, Ret ret = Ret()) {
    return static_cast<Ret>(
        (val >= 0) ?
        floor(val + (T)(.5)) :
        ceil( val - (T)(.5))
    );
}

int main()
{
    auto a = xround(5.5, int()); // = 6
    static_assert(std::is_same<decltype(a), int>::value, "");
    std::cout << a << "\n";       
    
    double b = xround(5.5); // = 6.0
    static_assert(std::is_same<decltype(b), double>::value, "");
    std::cout << b << "\n";
}    
