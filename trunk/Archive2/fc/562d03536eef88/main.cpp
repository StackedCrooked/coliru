#include <iostream>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/zip.hpp>
#include <boost/fusion/include/make_fused.hpp>

struct myf {
  template <class X, class Y>
  void operator()(X& x, Y& y) const 
  {
    std::cout << x + y << std::endl;
  }
  
  template <class X, class Y, class Z>
  void operator()(X& x, Y& y, Z& z) const
  {
      std::cout << x*(y+z) << std::endl;
  }
};

template <typename F, typename... Seqs>
void for_each(F f, Seqs const&... seqs)
{
    boost::fusion::for_each(boost::fusion::zip(seqs...),boost::fusion::make_fused(f));
}

int main() {
  boost::fusion::vector<int, double> x(1, 2.5);
  boost::fusion::vector<double, int> y(2, 5);
  boost::fusion::vector<double, double> z(3,7.5);
  myf F;
  for_each(F, x, y);
  for_each(F, x, y, z);
  return 0;
}