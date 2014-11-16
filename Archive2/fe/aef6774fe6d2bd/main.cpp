#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>

using namespace boost::multiprecision;
using namespace boost::flyweights;

/* Memoized calculation of Fibonacci numbers */

/* This class takes an int n and calculates F(n) at construction time */

struct compute_fibonacci;

/* A Fibonacci number can be modeled as a key-value flyweight
 * We choose the no_tracking policy so that the calculations
 * persist for future use throughout the program. See
 * Tutorial: Configuring Boost.Flyweight: Tracking policies for
 * further information on tracking policies.
 */

typedef flyweight<key_value<int,compute_fibonacci>,no_tracking> fibonacci;

/* Implementation of compute_fibonacci. Note that the construction
 * of compute_fibonacci(n) uses fibonacci(n-1) and fibonacci(n-2),
 * which effectively memoizes the computation.
 */
 
inline const cpp_int& value(const fibonacci& f);

struct compute_fibonacci:public cpp_int,private boost::noncopyable
{
  compute_fibonacci(int n):
    cpp_int(n==0?cpp_int(0):n==1?cpp_int(1):value(fibonacci(n-2))+value(fibonacci(n-1)))
  {}
};

inline const cpp_int& value(const fibonacci& f){return f.get();}

int main()
{
  /* list some Fibonacci numbers */

  for(int n=0;n<101;++n){
    std::cout<<"F("<<n<<")="<<fibonacci(n)<<std::endl;
  }

  return 0;
}
