#include <string>
#include <iostream>
 
void print(std::string::size_type n, std::string const &s)
{
    if (n == std::string::npos) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << "found: \"" << s.substr(n) << "\" at " << n << std::endl;
    }
}
 
int main()
{
    std::string::size_type n;
    std::string const s = "This is a string";
 
    // search backwards from end of string
    n = s.rfind("is");
    print(n, s);
    // search backwards from position 4
    n = s.rfind("is", 4);
    print(n, s);
    // find a single character
    n = s.rfind('s');
    print(n, s);
    // find a single character
    n = s.rfind('q');
    print(n, s);
}