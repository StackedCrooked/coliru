#include <boost/range/iterator_range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <iostream>

template <typename T>
boost::iterator_range<boost::filesystem::recursive_directory_iterator> traverse_directory(T const& dir) {
    boost::filesystem::recursive_directory_iterator f(dir), l;
    return boost::make_iterator_range(f, l);
}

static bool is_valid_file(boost::filesystem::directory_entry const& entry) {
    return is_regular_file(entry) && !is_other(entry);
}

int main(int argc, char* argv[])
{
    using namespace boost::adaptors;

    std::vector<std::string> const args(argv+1, argv+argc);

    for (auto& dir : args)
        for (auto& entry : traverse_directory(dir) | filtered(is_valid_file))
            std::cout << entry << "\n";
}