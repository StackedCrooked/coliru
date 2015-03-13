#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <string>


using boost::algorithm::replace_all;


std::string encode(std::string text, const std::string& del, const std::string& esc = "\\")
{
    replace_all(text, esc, esc + esc);
    replace_all(text, del, esc + del);
    return text;
}

std::string decode(std::string text, const std::string& del, const std::string& esc = "\\")
{
    replace_all(text, esc + del, del);
    replace_all(text, esc + esc, esc);
    return text;
}


int main(int, char** argv)
{
    if (std::string(argv[0]).find("decode") != std::string::npos)
    {
        std::cout << decode(argv[1], ",", "\\") << std::endl;
    }
    else
    {
        std::cout << encode(argv[1], ",", "\\") << std::endl;
    }
}
