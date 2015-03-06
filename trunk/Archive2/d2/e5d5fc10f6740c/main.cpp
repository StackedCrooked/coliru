#include <iostream>
#include <algorithm>

struct S
{
    template<class T, size_t N>
    void operator &(T (&ar)[N])
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }

    template<class T>
    void operator &(T*)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }
};

int main()
{
    int ar[1];
    int *p = ar;
    S s;
    
    s & ar;
    s & p;
}