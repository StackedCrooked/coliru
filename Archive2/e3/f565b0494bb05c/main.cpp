#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <string>
#include <algorithm>
#include <iostream>
namespace bi = boost::interprocess;

int main()
{
    bi::file_mapping file("a.out", bi::read_only);
    bi::mapped_region region(file, bi::read_only);
    auto beg = static_cast<const char*>(region.get_address());
    auto end = beg + region.get_size();
    std::string phrase = "zugzwang";
    auto i = std::search(beg, end, phrase.begin(), phrase.end());
    if (i != end)
        std::cout << phrase << " found at offset " << i - beg << '\n';
}
