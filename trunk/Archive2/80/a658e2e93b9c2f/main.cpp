#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include <boost/regex.hpp>

int main()
{
    std::string s{"a:1:1: warning: a [a]\nawefawef\nb:2:2: warning: b [b]\n"};
    boost::regex r{R"=(^(\w+?):(\d+?):(\d+?): warning: (\w+) \[(\w+?)\]$)="};

    boost::sregex_iterator it{std::begin(s), std::end(s), r};

    std::for_each(it, {}, [](decltype(*it)& match){
        std::cout << match.str() << std::endl;
    });
}
