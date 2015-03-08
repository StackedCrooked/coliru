#include <boost/container/flat_map.hpp>
#include <iostream>

using Elements = boost::container::flat_map<std::string, std::string>;

int main() {
    Elements map;
    map.reserve(256); // pre-allocate 256 "nodes"!

    map.insert({
            { "one",   "Eins"  },
            { "two",   "Zwei"  },
            { "three", "Drei"  },
            { "four",  "Vier"  },
            { "five",  "Fuenf" },
        });

    for (auto& e : map) {
        std::cout << "Entry: " << e.first << " -> " << e.second << "\n";
    }

    std::cout << "map[\"three\"] -> " << map.find("three")->second << "\n";
}
