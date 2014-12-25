#include <iostream>

class A
{
public:
   explicit A(int, int) {}
};

class B
{
public:
    B(int, int) {}
};

int main()
{
   B b = {1,2};
   A a = {1,2};
}