#include <boost/filesystem.hpp>
#include <boost/range.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main() {
    fs::path latest;
    std::time_t latest_tm {};

    for (auto&& entry : boost::make_iterator_range(fs::directory_iterator("."), {})) {
        if (entry.path().extension() == ".grb2") {
            std::time_t timestamp = fs::last_write_time(entry.path());
            if (timestamp > latest_tm) {
                latest = entry.path();
                latest_tm = timestamp;
            }
        }
    }

    if (latest.empty())
        std::cout << "Nothing found\n";
    else
        std::cout << "Last modified: " << latest << "\n";
}

