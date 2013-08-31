#include <iostream>
#include <string>
#include <vector>

struct A {
};

A func ()
{
    return A ();
}

int main()
{
    A &&ra = func ();      
}
