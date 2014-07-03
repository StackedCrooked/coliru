#include <iostream>

template<class T>
struct V 
{ 
    typedef T type; 
};

template<class T>
struct S
{
    // typename required in C++98/C++11
    typedef typename V<T>::type type;    
};

template<>
struct S<int>
{
    // typename not allowed in C++98, allowed in C++11
    // accepted by g++/Clang in C++98 mode as well (not by MSVC2010)
    typedef typename V<int>::type type;    
};

struct R
{
    // typename not allowed in C++98, allowed in C++11
    // accepted by g++ in C++98 mode as well (not by Clang/MSVC2010)
    typedef typename V<int>::type type;    
};

int main()
{
}
