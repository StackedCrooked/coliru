#include <iostream>
#include <algorithm>
#include <string>
int main ()
{
    std::string s = "This is an example";
    std::cout << s << '\n';
 
    s.erase(0, 5); // Erase "This "
    std::cout << s << '\n';
 
    while( auto it = std::find(s.begin(), s.end(), ' ') != s.end() )
    {
        s.erase(it);
    }
    std::cout << s << '\n';
 
    s.erase(s.find(' ')); // Trim from ' ' to the end of the string
    std::cout << s << '\n';
}