#include <iostream>

using namespace std;

class foo
{
    public:
     void bar1() { cout << "bar1\n"; }
     void bar2() const { cout << "bar2\n"; }
};

template <typename T, void (T::*mf)() const>
struct Test
{
   void call(T & obj) { (obj.*mf)(); }
};

int main()
{
  foo f;
  //Test<foo, &foo::bar1> t; // Doesnt compile
  //t.call(f);
  
  Test<foo, &foo::bar2> t2;
  t2.call(f);
  return 0;
}