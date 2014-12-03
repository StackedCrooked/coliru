#include <iostream>
#include <map>
#include <string>
#include <algorithm>

int main()
{
  std::map< std::string, int > my_map
  {
    { "Prtya", 5 }, 
    { "Sasha", 3 },
    { "Misha", 4 }
  };

  // only VS:
  //for each ( const auto& i in my_map )
  //  std::cout << i.first << ' ' << i.second << std::endl;

  // new for from C++11:
  //for ( const auto& i : my_map )
  //  std::cout << i.first << ' ' << i.second << std::endl;

  std::for_each( std::begin( my_map ), std::end( my_map ), []( const auto& i )
  {
    std::cout << i.first << ' ' << i.second << std::endl;
  } );

  return 0;
}