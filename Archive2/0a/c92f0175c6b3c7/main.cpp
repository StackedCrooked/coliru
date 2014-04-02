#include <iostream>

template <int N>
 int f2()
{
    std::cout << N << std::endl ;
    return N == 0 ? 1 : f2<N - 1>();
}

template <>
int f2<0>()
{
    return 0;
}


template <int N> struct Factorial
{
    enum 
    {
        value = N * Factorial<N - 1>::value
    };
};

template <> struct Factorial<0>
{
    enum
    {
        value = 1
    };
};


int main() 
{
    int x = f2<4>(); // compile error
    int n = Factorial<4>::value; // works fine
}