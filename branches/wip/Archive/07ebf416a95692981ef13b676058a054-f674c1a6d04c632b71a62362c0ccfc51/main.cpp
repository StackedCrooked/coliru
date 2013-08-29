#include <iostream>
#include <string>
#include <sstream>
using namespace std;
  
int main()
{  
    std::stringstream ss;
    ss << 5 << "wrear" << 42523;
    std::cout << ss.str();
    
    return 0;
}