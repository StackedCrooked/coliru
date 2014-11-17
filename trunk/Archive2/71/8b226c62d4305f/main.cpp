#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

using namespace boost::filesystem;

int main(int argc, char *argv[]) {
    path p(argc>1? argv[1] : ".");

    if(is_directory(p)) {
        std::cout << p << " is a directory containing:\n";

        for(auto& entry : boost::make_iterator_range(directory_iterator(p), {}))
            std::cout << entry << "\n";
    }
}
