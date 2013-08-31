#include<iostream>

class T {};

template<T* t>
class foo
{
    T ti = t;
};

int main()
{
   int x;
 foo<&x> f; //// What goes into ????
}
