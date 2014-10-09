#include <iostream>
#include <thread>
#include <utility>

template < typename T>
struct Base
{
 
  void foo(){ static_cast<T*>(this)->foo();}
  ~Base(){};
};

struct Bob : public Base<Bob>
{

  void foo(){std::cout << "Bob";}
    
};

template <typename T>
struct Alice
{
 
    Alice(Base<T> * b):_b(b){}
    
    Base<T>* _b;
};

int main()
{

    Bob b;
    Alice<Bob> a(&b);
   
}
