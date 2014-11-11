#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
int main()
{
    std::string in = "My name is xyzuik";
    std::string out;
    for(auto& w: boost::tokenizer<>(in))
        out = w + " " + out;
    std::cout << out << '\n';
}
