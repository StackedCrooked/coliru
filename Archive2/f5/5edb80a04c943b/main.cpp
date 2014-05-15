#include <iostream>
struct A
{
  A() { std::cout << "constructor" <<std::endl;};
  ~A() { std::cout << "destructor" <<std::endl;};
  
  A(const A&) { std::cout << "copy constructor" <<std::endl;};
  A(A&&) { std::cout << "move constructor" <<std::endl;};
  
    
};

struct B
{

 B( A a) : _a(std::move(a)){};    
    
  A _a;
};

struct C
{
  C( A&& a) : _a(std::move(a)){};    
    
  A _a;
};

struct D
{
  D(const A& a) : _a(a){};    
    
  A _a;
};

void f( A a){ B b(std::move(a));}
void g( A && a){ C c(std::move(a));}
void h( const A& a){ D d(a);}


int main()
{
    std::cout << " --------- with a temporary ----- \n";
    std::cout << " by value:\n";
    f(A());
    std::cout << " by rvalue ref:\n";
    g(A());
    std::cout << " by lvalue ref:\n";
    h(A());

}

