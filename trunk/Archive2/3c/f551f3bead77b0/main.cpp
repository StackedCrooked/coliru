#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <boost/logic/tribool.hpp>

struct B
{
  boost::tribool boo;

  void bug ()
  {
    bool tmp = indeterminate (boo);
    std::cout << "tmp = " << std::boolalpha << tmp << "\n";
    if (tmp && (boo = should_not_be_called ()) == false) {;}
  }

  bool should_not_be_called () const
  {
    std::cout << "BUG, wrong call\n";
    abort ();
  }
};

int main ()
{
  B a;
  a.bug ();
}
