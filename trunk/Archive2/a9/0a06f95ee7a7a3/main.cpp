#include <sstream>
#include <cassert>
 
int main()
{
   std::stringstream ss;
   ss << '!';
 
   int x = -1;
 
   assert(!(ss >> x)); // C++03 and C++11
   assert(x == -1);    // C++03
   assert(x == 0);     // C++11
}
