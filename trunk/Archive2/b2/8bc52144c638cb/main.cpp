#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <functional>
#include <set>
#include <iostream>

namespace fs = boost::filesystem;

fs::path find_directory(std::string const& name) {
    std::set<fs::path> visited;

    std::function<fs::path(fs::path const&)> recurse;
    recurse = [&visited, &name, &recurse](fs::path const& dir) -> fs::path {
        if (visited.insert(dir).second) { // not visited already
            try {
                for (auto& de : boost::make_iterator_range(fs::directory_iterator(dir), {})) {
                    if (fs::is_directory(de))
                    {
                        if (de.path().filename() == name)
                            return de.path();

                        // TODO check accessibility?
                        auto const& sub = recurse(de.path());

                        if (!sub.empty())
                            return sub;
                    }
                }
            } catch(fs::filesystem_error& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
        return {};
    };

    for (fs::path current : { ".", "..", "../..", "../../../" }) {
        auto const& sub = recurse(fs::canonical(current));
        if (!sub.empty())
            return sub;
    }

    return {};
}

int main() {
    std::cout << "FOUND " << find_directory("needle") << "\n";
}
