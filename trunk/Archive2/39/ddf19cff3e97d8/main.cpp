#include <iostream>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>

namespace bimaps = boost::bimaps;

int main()
{
   typedef boost::bimap<bimaps::multiset_of<int>, bimaps::set_of<int>> bimap_t;
   typedef bimap_t::value_type value_type;

   bimap_t bimap;
   bimap.insert(value_type(1, 1));
   bimap.insert(value_type(1, 2));
   bimap.insert(value_type(9, 15));

   for (auto e : bimap.left)
       std::cout << "LEFT\t" << e.first <<  " " << e.second << std::endl;

   for (auto e : bimap.right)
       std::cout << "RIGHT\t" << e.first <<  " " << e.second << std::endl;
}
