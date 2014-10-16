#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

using namespace boost;

int main()
{
    boost::iostreams::mapped_file_source f("main.cpp");
    boost::iterator_range<const char *> r(f.data(), f.data()+f.size());

    std::vector<iterator_range<const char *> > v;

    algorithm::split(v, r, is_any_of(" \n\t"), algorithm::token_compress_on);
    for (auto i : v)
        std::cout << "distance: " << std::distance(f.data(), i.begin()) << ", "
            << "length: " << i.size() << ", "
            << "value: '" << i << "'\n";

}
