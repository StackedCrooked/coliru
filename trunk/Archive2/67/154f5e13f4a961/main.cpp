#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>

using fileinfo_t = std::tuple<std::string, std::uint32_t>;

template <typename T>
auto name(T&& finfo) -> decltype(std::get<0>(std::forward<T>(finfo)))
{ 
    if (std::is_same<decltype(std::get<0>(std::forward<T>(finfo))), const std::string&>::value)
        std::cout << "decltype(std::get<0>(std::forward<T>(finfo))) == const std::string&" << std::endl;
    if (std::is_same<decltype(std::get<0>(std::forward<T>(finfo))), std::string&>::value)
        std::cout << "decltype(std::get<0>(std::forward<T>(finfo))) == std::string&" << std::endl;
    return std::get<0>(std::forward<T>(finfo)); 
}

template <typename T>
auto crc32(T&& finfo) -> decltype(std::get<1>(std::forward<T>(finfo)))
{
    if (std::is_same<decltype(std::get<1>(std::forward<T>(finfo))), const uint32_t&>::value)
        std::cout << "decltype(std::get<1>(std::forward<T>(finfo))) == const uint32_t&" << std::endl;
    if (std::is_same<decltype(std::get<1>(std::forward<T>(finfo))), uint32_t&>::value)
        std::cout << "decltype(std::get<1>(std::forward<T>(finfo))) == uint32_t&" << std::endl;
    return std::get<1>(std::forward<T>(finfo)); 
}

fileinfo_t test() { return fileinfo_t{"aaa", 11}; }

void print(const fileinfo_t& line)
{     
    std::cout << name(line) << ":" << crc32(line) << std::endl;
}

int main()
{
    fileinfo_t line;
    std::tie(name(line), crc32(line)) = test();
    print(line);
}