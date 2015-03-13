#include <iostream>


/*template <int I>
void f(int(&)[24 / (4 - I)])
{
        std::cout << "first" << std::endl;
}


template <int I>
void f(int(&)[24 / (4 + I)])
{
        std::cout << "second" << std::endl;
}*/

template <int I>
void foo(int (&)[5/I])
{}

/*template <int I>
void foo(int (&)[5/(I + 1)])
{}*/


int main()
{
        &foo<0>;
}

