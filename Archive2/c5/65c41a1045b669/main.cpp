#include <iostream>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost::adaptors;

struct pnt {
  char _name;
  int _type;
  bool _aux;
  };

int main() {

    std::vector<pnt> pnts;
    std::vector<int> pntType;

    boost::copy(pnts | transformed(std::mem_fn(&pnt::_type)), std::back_inserter(pntType));

    auto result = boost::copy_range<std::vector<int>>(pnts | transformed(std::mem_fn(&pnt::_type)));

}
