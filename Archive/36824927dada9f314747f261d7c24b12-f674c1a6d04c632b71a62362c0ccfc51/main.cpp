#include <iostream>
#include <string>
#include <vector>

template<typename T>
const std::string& demangle()
{
    static std::string result = [](std::string s) {
        auto offset = s.find("= ") + 2;
        return s.substr(offset, s.find(";") - offset);
    }(__PRETTY_FUNCTION__);
    return result;
}

int main()
{
    std::cout << demangle<int>() << std::endl;
    std::cout << demangle<std::string>() << std::endl;
    std::cout << demangle<std::vector<int>>() << std::endl;
}