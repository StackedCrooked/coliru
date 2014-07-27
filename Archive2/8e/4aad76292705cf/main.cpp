#include <iostream>


using namespace std;

struct tp 
{
    template<typename T>
    void foo() { cout << "Type parameter\n"; }   
    
    template<int Value>
    void foo() { cout << "Value parameter\n"; }   
};

int main() 
{
  const int x = 1;
  const int y = 2;
  const int z = 3;
  
  tp t1;
  t1.foo<x*y+z>();
  t1.foo<decltype(x*y+z)>();
  t1.foo<int>();
  
  return 0;
}