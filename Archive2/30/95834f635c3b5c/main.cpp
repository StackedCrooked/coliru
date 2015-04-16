#include <boost/phoenix.hpp>
#include <iostream>
#include <ostream>

using namespace std;
using namespace boost;
using namespace phoenix;
using namespace arg_names;
using namespace local_names;

int main()
{
   // capture by reference:
   cout <<
      (lambda(_a=_1)[_1 + _a ])(1)(2)
   << endl;
   cout <<
      (lambda(_b=_1)[lambda(_a=_1)[_1 + _a + _b ]])(1)(2)(3)
   << endl;
   // capture by value:
   cout <<
      (lambda(_a=val(_1))[_1 + _a ])(1)(2)
   << endl;
   cout <<
      (lambda(_b=val(_1))[lambda(_a=val(_1))[_1 + _a + _b ]])(1)(2)(3)
   << endl;
}