#include <iostream>
#include <functional>

template<typename F, typename T>
auto opby(F func, T arg)
{
    return [&](auto val) {
        return func(val, arg); 
    };
}


int main()
{
 auto mu = opby(std::multiplies<int>(), 2); 
 std::cout << mu(3) << std::endl;
}
