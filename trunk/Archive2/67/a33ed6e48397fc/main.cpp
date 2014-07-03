#include <string>
#include <sstream>
#include <iostream>

template <class T>
std::string to_string(const T& item)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    std::ostringstream ss;
    ss << item;
    return ss.str();
}

std::string to_string(const std::string& item)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return item;
}

std::string to_string(std::string&& item)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return std::move(item);
}

int main()
{
    std::string s("Hello, World!");
    std::cout << to_string(s) << std::endl;
    
    std::cout << to_string(std::string("Hello, World!")) << std::endl;
    std::cout << to_string(20) << std::endl;
}

    