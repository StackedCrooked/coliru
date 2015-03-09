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

    // OPTIONALLY: free up system allocations in fixed size pools
    // Two sizes, are implementation specific. My 64 system has the following:
    boost::singleton_pool<boost::fast_pool_allocator_tag, 8>::release_memory();  // the bucket pointer allocation
    boost::singleton_pool<boost::fast_pool_allocator_tag, 32>::release_memory(); // the ptr_node<std::pair<std::string const, std::string> >
}
