#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <string>


int main()
{
    std::string http = "HTTP 1.0 /test\r\ncontent-length: 2\r\ncurrent-time: 4\r\ndata";

    using namespace boost::algorithm;

    for (auto it = make_split_iterator(http, first_finder("\r\n")); it != decltype(it)(); ++it)
    {
        const auto& segment = (*it);
        std::cout << "segment: " << segment;

        for (auto it = make_split_iterator(segment, first_finder(": ")); it != decltype(it)(); ++it)
        {
            std::cout << " [" << (*it) << "]";
        }
        std::cout << std::endl;
    }
}
