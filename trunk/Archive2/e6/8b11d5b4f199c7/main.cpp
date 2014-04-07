#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
 std::string s{ "    5678" };
 auto f(s.find("5"));
 if(f == std::string::npos)
 {
     std::cout << "f not found" << std::endl;
     return 1;
 }
 
 std::cout << "size: " << s.size() << std::endl;
 std::cout << "f: " << f << std::endl;
 
 auto b(std::find_if(s.rbegin() + (s.size() - f), s.rend(),
 [](char c){ return !std::isspace(c); }));
 if(b == s.rend())
 {
     std::cout << "b not found" << std::endl;
     return 1;
 }
 
 std::cout << "'" << s[f] << "'" << " '" << *b << "'" << std::endl;
 std::string range(b.base(), s.begin() + f + 1);
 std::cout <<  "'" << range << "'" << std::endl;
 std::cout << "done" << std::endl;
}