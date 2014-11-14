#include <iostream>
#define ECHO(S) \
    std::cout << __PRETTY_FUNCTION__ << ": " << S << '\n'
struct A
{
  A()
  {
    ECHO(this);
  }

  A(const A& a)
  {
    ECHO(this);
  }

  A(A&& a)
  {
    ECHO(this);
  }

  ~A()
  {
    ECHO(this);
  }
};

struct B
{
  const A& a_;
  B(const A& a) : a_{a}
  {
    ECHO(&a_);
  }
  ~B()
  {
    ECHO(&a_);
  }
};

struct C
{
  const A& a_;
  C(const A& a) : a_(a)
  {
    std::cout << "C: Constructor: " << &a_ << '\n';
  }
  ~C()
  {
    std::cout << __PRETTY_FUNCTION__ << "\n";
  }
};

int main()
{
  A a;
  {
    std::cout << "**********B\n";
    B b{a};
    std::cout << "Hello\n";
    //B b(a);
  }
  {
    std::cout << "**********C\n";
    C c{a};
    //C c(a);
  }
  return 0;
}