#include <iostream>
#include <algorithm>
#include <iterator>
 
template <class Container, class Size, class T>
bool consecutive_values(const Container& c, Size count, const T& v)
{
  return std::search_n(std::begin(c),std::end(c),count,v) != std::end(c);
}
 
int main()
{
   const char sequence[] = "1001010100010101001010101";
 
   std::cout << std::boolalpha;
   std::cout << "Has 4 consecuарzeros: "
             << consecutive_values(sequence,4,'0') << '\n';
   std::cout << "Has 3 consecutive zeros: "
             << consecutive_values(sequence,3,'0') << '\n';
}