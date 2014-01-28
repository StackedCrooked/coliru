#include <iostream>

template <typename T>
T Add (T t1, T t2)
{
    std::cout << "<typename T>" << std::endl ;
    return t1 + t2 ;
}

template <>
int Add<int> (int n1, int n2)
{
    std::cout << "<int>" << std::endl ;
    return n1 + n2 ;
}

template <>
int Add (int n1, int n2)
{
    std::cout << "<>" << std::endl ;
    return n1 + n2 ;
}

int main (void) 
{
    Add (5, 4) ;
    Add <int> (5, 4) ;
    Add <> (5, 4) ;

    return 0 ;
}
