#include <boost/pool/pool_alloc.hpp>
#include <unordered_map>
#include <iostream>

using RawMap = std::unordered_map<std::string, std::string>;
using Elements = std::unordered_map<
        std::string, std::string,
        RawMap::hasher, RawMap::key_equal,
        boost::fast_pool_allocator<RawMap::value_type>
    >;

int main() {
    {
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

    boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(Elements::value_type)>::release_memory(); // free up allocated nodes
}
