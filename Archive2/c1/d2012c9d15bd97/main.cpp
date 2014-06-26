#include <iostream>

template <typename T>
void foo(T t)
{
    std::cout << t << std::endl;
}

template 
    <
        typename T,
        void (*F)(T)
    >
void apply(T t)
{
    F(t);
}

int main()
{
    apply<int, foo>(42);
}
