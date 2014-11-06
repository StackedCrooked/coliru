#include <iostream>
#include <typeinfo>


template<typename T, typename R, typename ...Args>
void check(R(T::*)(Args...) const)
{
    std::cout << "return type: " << typeid(R).name() << " arity: " << sizeof...(Args) << std::endl;
}


int main()
{
    auto lambda = [](int, int) { return true; };
    
    check(&decltype(lambda)::operator());
}

