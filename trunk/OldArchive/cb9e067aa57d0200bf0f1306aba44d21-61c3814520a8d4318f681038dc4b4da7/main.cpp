#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

struct A
{
    //implicit conversion to int
    operator int() { return 100; }

    //explicit conversion to std::string
    explicit operator std::string() { return "explicit"; } 
};

int main()
{
  const char16_t* s16 = u"\u00DA";
    
  cout << "\n\n\n\n\n                    Ok Good";
 
  return 0;  
}
