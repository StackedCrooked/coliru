
#include <sstream>
#include <iostream>

template<typename Stream, typename First>
void ToStream(Stream& ss, First&& v)
{
    ss << std::forward<First>(v);
}

template<typename Stream, typename First, typename ...Rest>
void ToStream(Stream& ss, First&& first, Rest&& ...rest)
{
    ToStream(ss, first);
    ToStream(ss, std::forward<Rest>(rest)...);
}

template<typename ...Args>
std::string ToString(Args&& ...args)
{
    std::stringstream ss;
    ToStream(ss, std::forward<Args>(args)...);
    return ss.str();
}

template<typename ...Args>
std::string ToString()
{
    return std::string();
}

int main()
{
    std::cout << ToString() << std::endl;
    
    std::cout << ToString("A") << std::endl;

    std::cout << ToString("A", std::endl<char, std::char_traits<char>>);
    
}
