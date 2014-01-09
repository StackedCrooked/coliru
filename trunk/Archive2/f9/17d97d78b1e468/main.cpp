#include <map>
#include <string>
#include <iostream>

#include <boost/any.hpp>

using variables_map = std::map<std::string, boost::any>;
using extractor = std::map<std::string, void(*)(boost::any const&)>;

int main()
{
    variables_map vm{{"deer", 10}, {"rating", 99.0}, {"name", "Chuck Norris"}};
    extractor extract{{"deer", [](boost::any const& in) {
                        std::cout << boost::any_cast<int>(in) << '\n';
                       }},
              {"rating", [](boost::any const& in) {
                        std::cout << boost::any_cast<double>(in) << '\n';
                       }},
              {"name", [](boost::any const& in) {
                        std::cout << boost::any_cast<char const *>(in) << '\n';
                       }}};
                       
    for(auto const& v : vm ) {
        std::cout << v.first << " = ";
        extract[v.first](v.second);
    }
}
