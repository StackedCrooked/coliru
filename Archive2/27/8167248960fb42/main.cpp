#include <iostream>
#include <thread>
#include <utility>

struct Base
{
 
  virtual void foo();
  virtual ~Base();
}
struct Bob : public BAse
{

  void foo(){std::cout << "Bob";}
    
};

struct Alice
{
 
    Alice(Base * b):_b(b){}
    
    Base* b;
}

int main()
{

   
   
}
