#include <iostream>
#include <vector>
#include <boost/filesystem.hpp> // or <experimental/filesystem> in modern C++

namespace fs = boost::filesystem;
int main(int ac, char** av) try
{
    if (ac < 2) {
        std::cout << "Usage: " << av[0] << " path\n";
        return 1;
    }

    fs::path p(av[1]);

    if(!exists(p) || !is_directory(p)) {
        std::cout << p << " is not a path\n";
        return 1;
    }

    fs::recursive_directory_iterator begin(p), end;
    std::vector<fs::directory_entry> v(begin, end); // vector created here

    std::cout << "There are " << v.size() << " files: \n";
    for(auto& f: v)
        std::cout << f << '\n';
} catch(std::exception& e) {
    std::cout << e.what() << '\n';
}
