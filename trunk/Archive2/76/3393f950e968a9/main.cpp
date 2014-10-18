#include <iostream>
#include <string>
int main()
{
    std::string s = "Ex";
    std::string& r1 = s;
    const std::string& r2 = s;
 
    r1 += "ample"; // modifies s
//  r2 += "!"; // error: cannot modify through reference to const
    std::cout << r2 << '\n'; // prints s, which now holds "Example"
}