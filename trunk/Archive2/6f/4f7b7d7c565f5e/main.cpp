#include <boost/filesystem.hpp>
#include <boost/range.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main() {
    fs::path latest;
    std::time_t latest_tm {};

    for (auto&& entry : boost::make_iterator_range(fs::directory_iterator("."), {})) {
        fs::path p = entry.path();
        if (is_regular_file(p) && p.extension() == ".grb2") 
        {
            std::time_t timestamp = fs::last_write_time(p);
            if (timestamp > latest_tm) {
                latest = p;
                latest_tm = timestamp;
            }
        }
    }

    if (latest.empty())
        std::cout << "Nothing found\n";
    else
        std::cout << "Last modified: " << latest << "\n";
}
