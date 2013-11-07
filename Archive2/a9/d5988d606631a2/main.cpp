#include <iostream>
#include <boost/shared_ptr.hpp>

struct A
{
protected:
 ~A(){}
};

struct B : A
{
  ~B()
  {
      std::cout <<"~B::B" << std::endl;
  }
};

int main()
{
  std::shared_ptr<A> v(new B());
}
