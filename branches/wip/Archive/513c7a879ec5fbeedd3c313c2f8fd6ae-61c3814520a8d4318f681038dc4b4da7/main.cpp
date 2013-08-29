#include<iostream>

#define UNIQUE(name) name ## __LINE__

class foo
{
   public:
   foo() { std::cout << "foo"; }
};

int main ()
{
   UNIQUE(foo);
}