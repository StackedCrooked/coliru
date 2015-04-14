#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/function.hpp>
#include <set>
#include <iostream>

namespace fs = boost::filesystem;

fs::path find_directory(std::string const& name) {
    struct helper {
        std::string const& name;
        helper(std::string const& name) : name(name) {}
        std::set<fs::path> visited;
        fs::path visit(fs::path const& dir) {
            if (visited.insert(dir).second) { // not visited already
                try {
                    for (fs::directory_iterator f(dir), l; f!=l; ++f)
                    {
                        if (fs::is_directory(*f))
                        {
                            if (f->path().filename() == name)
                                return f->path();

                            // TODO check accessibility?
                            fs::path const& sub = visit(f->path());

                            if (!sub.empty())
                                return sub;
                        }
                    }
                } catch(fs::filesystem_error& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            }
            return fs::path();
        }
    } visitor(name);

    char const* roots[] = { ".", "..", "../..", "../../../", 0 };
    for (const char** current = roots; *current; ++current) {
        fs::path sub = visitor.visit(fs::canonical(*current));
        if (!sub.empty())
            return sub;
    }

    return fs::path();
}

int main() {
    std::cout << "FOUND " << find_directory("needle") << "\n";
}
