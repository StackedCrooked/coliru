#include <iostream>
template<class T>
struct A
{
    T n;
};

template<class T>
struct B : A<T>
{
    // VC++ 2013 : OK
    // g++   : error: invalid use of template-name 'A' without an argument list
    // clang : error : use of class template 'A' requires template arguments
    B& f1(const A& obj)
    {
        return *this;
    }

    // VC++  : OK
    // g++   : OK
    // clang : OK
    B& f2(const A<T>& obj)
    {
        return *this;
    }
};

int main()
{
    B<int> b;

    return 0;
}
