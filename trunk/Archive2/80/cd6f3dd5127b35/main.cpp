#include <iostream>

struct A {
    enum E : int;
};

struct B : A {};

enum B::E : int { x = 2 };

int main()
{ 
}