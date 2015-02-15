#include <boost/filesystem.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <map>
#include <iostream>
#include <string>
#include <cstdio>

namespace fs = boost::filesystem;

template <
    typename KeyFunc,
    typename OutputUnique,
    typename HandleDupe,
    typename Path = boost::filesystem::path,
    typename KeyType = decltype(std::declval<KeyFunc>()(Path{})),
    typename Record = std::pair<boost::optional<KeyType> const, Path>
>
void files(std::string const& curdir, OutputUnique output, KeyFunc const& key, HandleDupe const& handler)
{
    using namespace boost::adaptors;
    using namespace boost;

    using path  = fs::path;
    using paths = std::vector<path>;

    auto safe_key = [&key](path const& p) { 
        optional<KeyType> sz;
        try { sz = key(p); } catch(...) { }
        return std::make_pair(sz, p); 
    };

    std::function<void(path const&)> recurse = [&](path const& curdir) {
        paths files;
        paths dirs;

        std::map<optional<KeyType>, path> seen;

        try {
            auto entries 
                = make_iterator_range(fs::directory_iterator(curdir), {})
                | transformed(std::mem_fn(&fs::directory_entry::path))
                ;

            std::partition_copy(
                    entries.begin(), entries.end(),
                    back_inserter(dirs),
                    back_inserter(files),
                    [](path const& p) { return is_directory(p); }
                );

            if (!files.empty()) {
                for(auto& f: files) {
                    auto insertion = seen.insert(safe_key(f));

                    if (!insertion.second && insertion.first->first)
                        handler(*insertion.first, safe_key(f));
                    else
                        *output++ = f;
                }
            }

            boost::for_each(dirs, recurse);
        } catch(std::exception const& e) {
            std::cerr << "Skipping " << curdir << ": " << e.what() << "\n";
        }
    };

    recurse(curdir);
}

template <typename OutputUnique = std::ostream_iterator<fs::path> >
void files(std::string const& curdir = ".", OutputUnique output = std::ostream_iterator<fs::path>(std::cout, "\n"))
{
    using fs::path;
    using Record = std::pair<boost::optional<size_t> const, path>;
    files(
            curdir,
            output, 
            [](path const&p) { return file_size(p); },
            [](Record const&, Record const&) { }
         );
}

#include <boost/function_output_iterator.hpp>

int main() { 
    files("."); // prints non-dupes recursively

    // advanced use: print nothing for non-dupes, but print the duplicate pairs
    auto devnull = boost::make_function_output_iterator([](fs::path){});
    files(".", 
            devnull,                                     // back_inserter(some_vector), etc.
            [](fs::path const& p){return file_size(p);}, // some other key? 
            [](auto const& dupe, auto const& orig) {
                std::cout << "Duplicate size (" << *dupe.first << ") in " << dupe.second << "\n"
                          << "\tOriginal: " << orig.second << "\n";
            }); 
}
