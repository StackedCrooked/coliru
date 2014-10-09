#include <iostream>
#include <thread>
#include <utility>

template < typename T>
struct Base
{
 
  void foo(){ static_cast<T*>(this)->foo_impl();}
  ~Base(){};
};

struct Bob : public Base<Bob>
{

  void foo_impl(){std::cout << "Bob";}
    
};

template <typename T>
struct Alice
{
 
    Alice(Base<T> * b):_b(b){}
    
    Base<T>* _b;
};

template<typename T>
void bar(Base<T> *b)
{
    b->foo();
}    
int main()
{

    Bob b;
    Alice<Bob> a(&b);
   
    bar<Bob>(&b);
}
