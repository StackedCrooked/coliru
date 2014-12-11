#include <iostream>
#include <cmath>

template<typename T = double>
T f() {
    return static_cast<T>(INFINITY);
}

int main()
{
    std::cout << f() << std::endl;
    std::cout << f<float>() << std::endl;
    std::cout << f<long double>() << std::endl;
    
    // for the following types std::numeric_limits::has_infinity is false
    std::cout << std::numeric_limits<bool>::has_infinity << " " << f<bool>() << std::endl;
    std::cout << f<int>() << std::endl;
    std::cout << f<long long>() << std::endl;
    std::cout << f<unsigned long long>() << std::endl;
}
