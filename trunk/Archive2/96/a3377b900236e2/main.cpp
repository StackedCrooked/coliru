#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>

int main() {
    std::vector<std::string> split_;
    std::string line("one;two#three//four five\r\n"
            "six");
    boost::split(split_,line,
            !(
                boost::is_from_range('a','z') || 
                boost::is_from_range('A','Z') || 
                boost::is_from_range('0','9')
             )
            );

    for(auto const& s : split_)
        std::cout << s << "\n";
}
