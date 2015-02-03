#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/algorithm.hpp>
#include <vector>
#include <iostream>
#include <map>

int main() {
    using boost::filesystem::path;
    using boost::filesystem::directory_iterator;
    using boost::make_iterator_range;

    path p("."); // or "C:\\Customer\\AppleFruit\\"

    std::map<std::string, std::vector<path> > bins {
        { "In_",  {} },
        { "Out_", {} },
      //{ "",     {} }, // remaining files
    };

    for(auto&& de: make_iterator_range(directory_iterator("."), {}))
        for(auto& bin: bins)
            if (de.path().filename().native().find(bin.first) == 0)
                bin.second.push_back(std::move(de));

    for(auto& bin: bins)
        for(auto& f : bin.second)
            std::cout << "Prefix '" << bin.first << "': " << f << "\n";
}
