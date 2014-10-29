#include <iostream>
#include <tuple>

using fileinfo_t = std::tuple<std::string, std::uint32_t>;

std::string&   name(fileinfo_t& finfo)  { return std::get<0>(finfo); }
std::uint32_t& crc32(fileinfo_t& finfo) { return std::get<1>(finfo); }

const std::string&   name(const fileinfo_t& finfo)  { return std::get<0>(finfo); }
const std::uint32_t& crc32(const fileinfo_t& finfo) { return std::get<1>(finfo); }

fileinfo_t test() { return fileinfo_t{"aaa", 11}; }

int main()
{
    fileinfo_t line;
    std::tie(name(line), crc32(line)) = test();
    
    std::cout << name(line) << ":" << crc32(line) << std::endl;
}