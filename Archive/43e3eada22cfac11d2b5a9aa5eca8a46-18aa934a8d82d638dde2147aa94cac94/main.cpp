#include<iostream>

class T {};

template<T* t>
class foo
{
    T* ti = t;
};

int x;

int main()
{
   foo<&x> f; //// What goes into ????
}
