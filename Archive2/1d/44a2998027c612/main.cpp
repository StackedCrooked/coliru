#include <iostream>

enum A
{
    one = 0,
    two = 1
};

enum B
{
    three = 3
};

template <typename T>
void foo(T x);

template <>
void foo<A>(A x)
{
    std::cout << "A" << std::endl;
}

template <>
void foo<B>(B x)
{
    std::cout << "B" << std::endl;
}

int main()
{
    foo(three);
   // foo<B>();
   // foo_for_a(one);
}