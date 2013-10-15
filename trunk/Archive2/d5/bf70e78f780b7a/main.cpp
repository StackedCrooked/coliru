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
        "James Britton <James.Britton@simplivity.com>",
        "Jenn Nicoletti <Jenn.Nicoletti@simplivity.com>",
        "Lou Cordero <Lou.Cordero@simplivity.com>",
        "Mark Aikens <Mark.Aikens@simplivity.com>", 
        "Matthew McShane <Matthew.McShane@simplivity.com>",
        "Mike Stack <Mike.Stack@simplivity.com>",
        "Omayre Zahid <Omayre.Zahid@simplivity.com>",
        "Paul Natusch <Paul.Natusch@simplivity.com>",
        "Tom Alborough <Tom.Alborough@simplivity.com>",
        "Vince Coccia <Vince.Coccia@simplivity.com>",
        "Xian Pan <xian.pan@simplivity.com>",
        "Yan Xiao <Yan.Xiao@simplivity.com>",
        "Yidong Wang <yidong.wang@simplivity.com>"
    };
    std::shuffle(begin(names), end(names), g);
    std::copy(begin(names), end(names), 
              std::ostream_iterator<std::string>(std::cout, "\n"));
}
