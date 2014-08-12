#include <iostream>
#include <string>
#include <boost/bimap.hpp>

template<typename MapType>
void print_map(const MapType &m)
{
   typedef typename MapType::const_iterator const_iterator;
   for( const_iterator iter = m.begin(), iend = m.end(); iter != iend; ++iter )
     std::cout << iter->first << "-->" << iter->second << "\n";
}

int main ()
{
   typedef boost::bimap<int, std::string> is_bm;
   is_bm bm;
   bm.insert( is_bm::value_type(1, "one" ) );
   bm.insert( is_bm::value_type(2, "two" ) );
   bm.insert( is_bm::value_type(3, "three" ) );
   print_map( bm.left );
   print_map( bm.right );
   
   return 0;
}