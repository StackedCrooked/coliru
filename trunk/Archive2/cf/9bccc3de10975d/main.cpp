#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

int main()
{
   typedef boost::bimap<boost::bimaps::multiset_of<int>, boost::bimaps::set_of<int>> bimap_t;
   typedef bimap_t::value_type value_type;

   bimap_t bimap;
   bimap.insert(value_type(1, 1));
   bimap.insert(value_type(10, 50)); 
   bimap.insert(value_type(1, 2));
   bimap.insert(value_type(9, 15));   

   for (auto& e : boost::make_iterator_range(bimap.left.equal_range(1)))
       std::cout << "LEFT\tKey = " << e.first << "    Value = " << e.second << std::endl;

   for (auto& e : boost::make_iterator_range(bimap.right.equal_range(1)))
       std::cout << "RIGHT\tKey = " << e.first << "    Value = " << e.second << std::endl;
}
