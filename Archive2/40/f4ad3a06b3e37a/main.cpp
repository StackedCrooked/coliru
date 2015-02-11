#include <iostream>


// pretend liike vtable 
template<typename T, typename F>
auto Get(F&&) -> void(*&)(const T&) 
{
    using Fptr = void(*)(const T&);
    static Fptr ptr = [](const T&) { std::cout << "Default implementation\n"; };
    return ptr;
}


template<typename T>
void foo(const T& t)
{
    Get<T>(&foo<T>)(t);
}


int main()
{
    foo(1);
    foo(false);
    
    // override foo(int)
    Get<int>(&foo<int>) = [](const int& n) { std::cout << "n=" << n << std::endl; };
    
    
    foo(1);
}
