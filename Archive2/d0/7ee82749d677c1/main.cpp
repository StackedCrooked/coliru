#include <iostream>
#include <string>
#include <boost/bimap.hpp>

template<typename MapType>
void print_map(const MapType &m)
{
   typedef typename MapType::const_iterator c_iterator;
   for( c_iterator iter = m.begin(), iend = m.end(); iter != iend; ++iter )
     std::cout << iter->first << "-->" << iter->second << "\n";
}

template<typename MapType>
void print_mapr(const MapType &m)
{
   typedef typename MapType::const_reverse_iterator cr_iterator;
   for( cr_iterator iter = m.rbegin(), iend = m.rend(); iter != iend; ++iter )
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
   print_mapr( bm.left );
   print_mapr( bm.right );
   
   return 0;
}