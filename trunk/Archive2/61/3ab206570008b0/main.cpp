#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <math.h>

#define UNUSED(x)  (void)x

using std::cerr;
using std::cout;
using std::endl;
// new 10/3/14
using std::overflow_error;
// ... AND chgd refs below to omit "std::" namespace prefix
using std::string;

#define _FAIL
// uncomment the above line to see things break

typedef unsigned long ulong;

class SixFactor
{
public:
  SixFactor(const ulong m, const int o): _mult(m), _offs(o) {};

#define ABS(x) fabs(x)

  operator string() const {
    std::ostringstream os;
    os << "6*" << _mult;
    if (_offs < 0)
      os << " - " << ABS(_offs);
    else
      os << " + " << _offs;

    return os.str();
  }

  SixFactor operator*(const SixFactor &othr) throw(overflow_error) {
    UNUSED(othr);

#ifdef _FAIL
    std::string err_msg = "SixFactor mult. overflow -- doesn't matter what's here";  // unused
#endif
    throw overflow_error("does this work?");
  }

  SixFactor& operator=(const SixFactor &b) {
    _mult = b._mult;
    _offs = b._offs;

    return *this;
  }

protected:
  ulong _mult;
  int _offs;    // -1 or +1
  // private:
  //   std::string err_msg;
};


#define CHAR char
#define ATOL atol
#define MAIN main

int MAIN(int argc, CHAR* argv[])
{
  UNUSED(argc);
  UNUSED(argv);

  SixFactor t(26757, -1);
  cout << "t = " << static_cast<string>(t) << endl;
  try {
    SixFactor e(0,0);
    e = t*t;
    cout << "got here - no exception" << endl;
  } catch (overflow_error &oe) {
    cout << "caught overflow exception: " << oe.what() << endl;
  } catch (...) {
    cout << "caught an unknown exception" << endl;
  }

  return 0;
}