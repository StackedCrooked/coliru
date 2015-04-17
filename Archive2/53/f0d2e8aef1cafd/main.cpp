#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <complex>

namespace my {
void *p_null = NULL;
}

template<class opt_type>
void foo(opt_type *o1 = my::p_null)
{
  if (o1) {
    std::cout << "foo_o1" << std::endl;
  } else {
    std::cout << "foo_NULL" << std::endl;
  }
}

void foo() {
  std::cout << "No foo\n";
}

int main()
{
    typedef std::complex<double> mytype;
    mytype a;
    foo(&a);
    foo(my::p_null);
    foo<std::complex<double> >(NULL);
    foo();
    // foo(a); fails to compile
    return 0;
}