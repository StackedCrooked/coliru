#include <iostream>
#include <string>
#include <vector>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/zip.hpp>
#include <boost/fusion/include/make_fused.hpp>

/**
 * Base case - only one sequence,
 * just forward to fusion::for_each
 */
template<class Function, class Sequence>
void for_each_combination(Function && f, Sequence && s)
{
    boost::fusion::for_each(std::forward<Sequence>(s), std::forward<Function>(f) );
}

/**
 * General case
 */
template<class Function, class Head, class ... Sequences>
void for_each_combination(Function && f, Head && s, Sequences && ... tail)
{
    // We call for_each for every element on the first sequence, "s"
    boost::fusion::for_each(std::forward<Head>(s),
        [&](auto x) 
        {
            // x is an element of "s"
            // Call for_each_combination again,
            // but with a function f which has the first argument already bounded.
            // Pass the remaining sequences as additional arguments
            for_each_combination(
                [&](auto && ... args)
                {
                    f(x, args ... );
                },
                std::forward<Sequences>(tail) ... );
            
        });
}

struct myf {
  template <class X, class Y>
  void operator()(X& x, Y& y) {
    std::cout << x + y << std::endl;
  }
};

int main() {
  boost::fusion::vector<int, double> x(1, 2.5);
  boost::fusion::vector<double, int> y(2, 5);
  myf F;
  for_each_combination(F, x, y);
  return 0;
}
