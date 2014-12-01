#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <boost/logic/tribool.hpp>

struct B
{
  mutable boost::tribool boo;

  void bug (B const& x)
  {
	bool tmp = indeterminate (x.boo);
	std::cout << "tmp = " << std::boolalpha << tmp << "\n";
    // tmp is false, thus x.should_not_be_called should not be called ;)
	if (tmp && !(x.boo = x.should_not_be_called ())) {;}
  }

  bool should_not_be_called () const
  {
  	std::cout << "BUG, wrong call\n";
  	abort ();
  }
};

int main ()
{
	B a, b; b.boo = true;
	a.bug (b);
}