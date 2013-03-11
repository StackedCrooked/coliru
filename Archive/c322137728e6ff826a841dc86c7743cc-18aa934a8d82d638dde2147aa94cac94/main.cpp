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
 foo<int, ????> f; //// What goes into ????
}
