#include<iostream>

#define UNIQUE_1(name, x) name ## x
#define UNIQUE(name) UNIQUE_1(name, __LINE__)

class foo
{
   public:
   foo() { std::cout << "foo"; }
};

int main ()
{
  foo  UNIQUE(foo);
}