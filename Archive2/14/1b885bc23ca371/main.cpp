#include <iostream>

enum class Stuff
{
    A,
    B,
};

template<Stuff S>
struct Thing {};


template<>
struct Thing<Stuff::A>
{
    using type = int;
};

int main()
{
    Thing<Stuff::A>::type x = 1; // yay
    Thing<Stuff::B>::type y = 2; // nay
    
}
