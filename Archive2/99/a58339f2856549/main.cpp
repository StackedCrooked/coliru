#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#include <algorithm>    // std::transform

template<typename T>
std::string to_string(const T& ntf);
std::string to_string(std::vector<std::string> list );

int main()
{
    std::cout << "start" << std::endl;    
    std::string x = to_string({to_string(1), to_string(123)});
    std::cout << x << std::endl;
    x = to_string({to_string(2), to_string(123.23), to_string("askd")});
    std::cout << x << std::endl;
    x = to_string({to_string(3), to_string(123), to_string("askd"), to_string(12.1245)});
    std::cout << x << std::endl;
}

template<typename... T>
std::string variadicTemplate(T... args)
{
//    to_string(args...);
}

template<typename T>
std::string to_string(const T& ntf)
{
    std::stringstream ss;
    ss  << ntf;
    return ss.str();
}

std::string to_string(std::vector<std::string> list ) {
    
    std::string out;
    transform(list.begin(), list.end(), list.begin(), 
        [&](std::string s)
        {
            out = out + s;
            return "";
        }
    );
    
    return out;
    
}
