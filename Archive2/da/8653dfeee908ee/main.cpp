#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

std::ostream & operator<<( std::ostream & os, const std::vector<int> & vec )
{
  for ( auto && e : vec)
    os << e << " ";
  return os;
}

int main()
{
  std::stringstream ss1, ss2;
  ss1 << 42;
  ss2 << 42;

  std::vector<int> vec1( std::istream_iterator<int>( ss1 ), std::istream_iterator<int>() );
  std::vector<int> vec2( std::istream_iterator<int>{ ss2 }, std::istream_iterator<int>() );

  std::cout << vec1 << std::endl;
  std::cout << vec2 << std::endl;
}