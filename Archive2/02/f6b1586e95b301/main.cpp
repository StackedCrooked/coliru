#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>

int main()
{
    std::mt19937 g(6506932725);
    std::vector<std::string> names{
        "James Britton",
        "Jenn Nicoletti",
        "Lou Cordero",
        "Mark Aikens", 
        "Matthew McShane",
        "Mike Stack",
        "Omayre Zahid",
        "Paul Natusch",
        "Tom Alborough",
        "Vince Coccia",
        "Xian Pan",
        "Yan Xiao",
        "Yidong Wang"
    };
    std::shuffle(begin(names), end(names), g);
    std::copy(begin(names), end(names), 
              std::ostream_iterator<std::string>(std::cout, "\n"));
}
