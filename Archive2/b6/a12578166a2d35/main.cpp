#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main()
{
    for(auto& f : boost::make_iterator_range(fs::directory_iterator("."), {}))
    {
        if (fs::is_regular(f))
            std::cout << fs::file_size(f) << "\t" << f << "\n";
    }
}