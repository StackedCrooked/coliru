#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <vector>

int main()
{
    auto const& s = "hello\r\nworld";

    std::vector<boost::iterator_range<char const*>> lines;
    boost::split(lines, s, boost::is_any_of("\r\n"), boost::token_compress_on);

    for (auto const& range : lines)
    {
        std::cout << "at " << (range.begin() - s) << ": '" << range  << "'\n";
    };
}