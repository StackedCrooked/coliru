#include <iostream>

template<class T>
T* address(T&& t)
{ return &t; }

//template<class T>
struct c
{
    static constexpr auto* x = false ? address([]{ std::cout << "hello\n"; }) : nullptr;
};

int main()
{
    (*c::x)();
}