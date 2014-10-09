#include <iostream>
#include <thread>
#include <utility>

struct Base
{
 
  virtual void foo();
  virtual ~Base(){};
};
struct Bob : public Base
{

  void foo(){std::cout << "Bob";}
    
};

struct Alice
{
 
    Alice(Base * b):_b(b){}
    
    Base* _b;
};

int main()
{

    Bob b;
    Alice a(&b);
   
}
