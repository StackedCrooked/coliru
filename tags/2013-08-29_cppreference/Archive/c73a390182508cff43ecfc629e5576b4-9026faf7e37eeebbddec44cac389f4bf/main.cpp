#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main() {
    const boost::regex r("^\\{ ([^\\}]*)\\s*\\}");
    boost::smatch match;
    std::string str = "{ #include \"index.h\" }";
    
    boost::regex_search(str, match, r, boost::match_continuous);
    
    std::cout << *match[1].first << *match[1].second << std::endl;
    std::cout << *match[1].first << *match[1].second << std::endl;
    std::cout << *match[1].first << *match[1].second << std::endl;
    
    std::cout << std::string(match[1].first, match[1].second) << std::endl;
    std::cout << *match[1].first << *match[1].second << std::endl;
    std::cout << std::string(match[1].first, match[1].second) << std::endl;
    std::cout << *match[1].first << *match[1].second << std::endl;
    std::cout << std::string(match[1].first, match[1].second) << std::endl;
    std::cout << *match[1].first << *match[1].second << std::endl;
    std::cout << std::string(match[1].first, match[1].second) << std::endl;
    std::cout << *match[1].first << *match[1].second << std::endl;
    std::cout << std::string(match[1].first, match[1].second) << std::endl;
    std::cout << *match[1].first << *match[1].second << std::endl;
}