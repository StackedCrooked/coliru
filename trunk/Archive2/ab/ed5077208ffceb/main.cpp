#include <array>
#include <iostream>

#include <boost/tuple/tuple.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/zip_iterator.hpp>

int main() 
{
  std::array<int, 4> a{{1, 2, 3, 4}};
  std::array<int, 4> b{{10, 20, 30, 40}};

  for(auto const& tup : 
        boost::make_iterator_range(
          boost::make_zip_iterator(boost::make_tuple(a.begin(), b.begin())),
          boost::make_zip_iterator(boost::make_tuple(a.end(), b.end())))) {
    std::cout << tup.get<0>() << ' ' << tup.get<1>() << '\n';
  }
}
