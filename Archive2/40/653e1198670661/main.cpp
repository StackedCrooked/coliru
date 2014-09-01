// sicp.1.1.3 Evaluating Combinations

#include <iostream>                        // cout, endl, << 
#include <boost/phoenix.hpp>               // arg1, arg2, +, *
#include <boost/fusion/container.hpp>      // make_list
#include <boost/fusion/algorithm.hpp>      // fold
  
using namespace boost::phoenix::arg_names; // arg1, arg2, +, *
using namespace boost::fusion;             // make_list, fold

//-----------------------------------------------------------------------------

template<typename T0, typename... TN>
auto add (T0 t0, TN... tn) { return fold(make_list(tn...), t0, arg1 + arg2); }

auto mul = arg1 * arg2;

auto print = [](auto v) {  std::cout << v << std::endl; };

//------------------------------------------------------------------------------

int main()
{ 
  //    (*   (+ 2 (* 4 6))
  //         (+ 3 5 7)) 
  print (mul (add (2, mul (4, 6)),
              add (3, 5, 7))); 
}
