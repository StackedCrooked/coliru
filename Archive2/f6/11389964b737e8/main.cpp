#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
   std::vector< std::pair<int,int> > seq { {1,2}, {3,4}, {1,1}, {3,5}, {3,2} } ;

   std::sort( std::begin(seq), std::end(seq) ) ;

   for( auto pair : seq)
        std::cout << '{' << pair.first << ',' << pair.second << "} " ;
   std::cout << '\n' ;
}
