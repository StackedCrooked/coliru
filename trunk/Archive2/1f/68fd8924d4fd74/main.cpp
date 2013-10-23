#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <memory>
using namespace std;

std::string convert_int(int n)
{
   std::stringstream ss;
   ss << setfill('0') << setw(2) << hex << n;
   return ss.str();
}

int main()
{
  const std::shared_ptr<std::string> first(new std::string("first"));  
  cout << "first ref count: " << first.use_count();
  std::shared_ptr<std::string> second(first);
  cout << "\n\nfirst ref count: " << first.use_count();
  cout << "\nsecond ref count: " << second.use_count();
}
