#include <regex>
#include <iostream>

int main()
{
    std::string s("hello world(12)");
    std::regex r("[^()\\s]+(?=[()])|[^\\s()]+|[()]");
    
    auto it  = std::sregex_iterator(s.begin(), s.end(), r);
    auto end = std::sregex_iterator();
    
    for ( ; it != end; ++it)
        std::cout << it->str() << '\n';
}
