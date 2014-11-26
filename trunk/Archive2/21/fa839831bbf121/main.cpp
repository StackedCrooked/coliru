#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

class Base
{
public:  
  virtual string gettype() { return typeid(this).name(); }
};

class Derived: public Base
{
};

int main()
{
  Base b;
  Derived d;

  Base & bref = d;
  cout << typeid(bref).name() << endl;
  cout << bref.gettype() << endl;

  Base * bptr = &d;
  cout << typeid(bptr).name() << endl;
  cout << bptr->gettype() << endl;

  if( dynamic_cast<Derived*>(bptr) )
    cout << "succeeded in dynamic_cast<Derived*>" << endl;

  return 0;
}