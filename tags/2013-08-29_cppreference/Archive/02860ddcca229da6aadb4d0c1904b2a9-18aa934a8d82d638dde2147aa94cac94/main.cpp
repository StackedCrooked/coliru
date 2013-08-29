#include<iostream>

class T {};

template<typename T, T t>
class foo
{
    T ti = t;
};

int main()
{
    int* t;
 foo<int, int(42)> f; //// What goes into ????
}
