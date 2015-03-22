#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main(int argc, char* argv[])
{
    std::string s = "log entry: %d{%H.%M.%s} %t %n %m";
    
    boost::regex re("(%.(\\{.*\\}){0,1})");
    boost::smatch m;
    boost::regex_match(s, m, re);
    
    std::cout << m.size() << std::endl;
//    
//    auto beg = std::sregex_iterator(s.begin(), s.end(), re);
//    auto end = std::sregex_iterator();
    
    return 0;
}