#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <fstream>
#include <iterator>

#include <iostream>

int main()
{
    boost::iostreams::mapped_file_source haystack("100words");
    auto f(haystack.data()), l(haystack.data() + haystack.size());

    typedef std::reverse_iterator<boost::iostreams::mapped_file::const_iterator> rit;

    std::string const pattern = "the";

    for (auto m = f; l != (m = boost::algorithm::boyer_moore_search(m, l, pattern)); ++m)
    {
        auto sol = std::find(rit(m), rit(haystack.data()), '\n').base();
        m = std::find(m, l, '\n'); // eol

        std::cout << std::string(sol, m) << "\n";
    }
}
