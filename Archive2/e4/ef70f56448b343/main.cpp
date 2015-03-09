#include <boost/pool/pool_alloc.hpp>
#include <boost/unordered/unordered_map.hpp>
#include <iostream>

using RawMap = boost::unordered_map<std::string, std::string>;
using Elements = boost::unordered_map<
        std::string, std::string,
        RawMap::hasher, RawMap::key_equal,
        boost::fast_pool_allocator<RawMap::value_type>
    >;

int main() {
    Elements hashtable;

    hashtable.insert({
            { "one",   "Eins"  },
            { "two",   "Zwei"  },
            { "three", "Drei"  },
            { "four",  "Vier"  },
            { "five",  "Fuenf" },
        });

    for (auto& e : hashtable) {
        std::cout << "Hash entry: " << e.first << " -> " << e.second << "\n";
    }

    std::cout << "hashtable[\"three\"] -> " << hashtable.find("three")->second << "\n";
}
