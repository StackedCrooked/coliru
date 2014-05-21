#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iterator>
#include <algorithm>

int main()
{
    std::string s{"a:1:1: warning: a [a]\nb:2:2: warning: b [b]\n"};
    std::regex r{R"=((\w+?):(\d+?):(\d+?): warning: (\w+) \[(\w+?)\])="};

    std::sregex_iterator it{std::begin(s), std::end(s), r};

    std::for_each(it, {}, [](decltype(*it)& match){
        std::cout << match.str() << std::endl;
    });
}

