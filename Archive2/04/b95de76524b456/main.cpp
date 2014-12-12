#include <iostream>
using std::cout; 
using std::endl;

struct Foo
{
  Foo()
  {
    cout << "Foo" << endl;
  }
};


struct Bar
{
  Bar()
  {
    cout << "Bar" << endl;
  }
};

struct FooBar
{
  FooBar()
    : foo_()
    , bar_()
  {}

  Foo foo_;
  Bar bar_;
};

struct BarFoo
{
  BarFoo()
    : foo_()
    , bar_()
  {}

  Bar bar_;
  Foo foo_;
};

int main(int argc, char* argv[])
{
  FooBar foobar;
  BarFoo barfoo;
  system("Pause");
  return 0;
}