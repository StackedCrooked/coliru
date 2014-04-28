#include <iostream>
#include <sstream>

int main()
{
  std::stringstream s;
  s << std::hex;

  int i;

  s << "100";
  s >> i;     // 256
  
  std::cout << i << '\n';

  s.str("");
  s.clear(); // might not be necessary if you check stream state above before and after extraction

  s << "10";  // doesn't work
  s >> i;
  
  std::cout << i << '\n';
}