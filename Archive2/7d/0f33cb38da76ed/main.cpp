#include <iostream>

template <typename T>
T foo()
{
    return T();
}

template 
    <
        typename T,
        T (*F)()
    >
void apply(T& t)
{
    t =  F();
}

int main()
{
    int i;
    
    apply<int, foo>(i);
    std::cout << i << std::endl;
}
