#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

int main()
{
    std::string s = "hiAAAmyAAAnameAAAis";
    std::vector<std::string> v;
    
    split(v, s, boost::is_any_of("A"), boost::token_compress_on);
    
    for(auto& s: v)
        std::cout << s << '\n';
}