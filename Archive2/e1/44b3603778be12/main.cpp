#include <boost/intrusive/unordered_set.hpp>
#include <boost/intrusive/unordered_set_hook.hpp>
#include <iostream>

namespace bi = boost::intrusive;

struct Element;

namespace boost {
    template <> struct hash<Element> {
        size_t operator()(Element const& e) const;
    };
}

struct Element : bi::unordered_set_base_hook<> {
    std::string key;
    mutable std::string value;

    Element(std::string k = "", std::string v = "") 
        : key(std::move(k)), value(std::move(v)) { }

    bool operator==(Element const& other) const { return key == other.key; }
};

size_t boost::hash<Element>::operator()(Element const& e) const {
    return hash_value(e.key); 
}

using Elements = bi::unordered_set<Element>;

int main() {
    std::array<Element, 256> storage;               // reserved 256 entries
    std::array<Elements::bucket_type, 100> buckets; // buckets for the hashtable

    Elements hashtable(Elements::bucket_traits(buckets.data(), buckets.size()));

    storage[0] = { "one",   "Eins"  };
    storage[1] = { "two",   "Zwei"  };
    storage[2] = { "three", "Drei"  };
    storage[3] = { "four",  "Vier"  };
    storage[4] = { "five",  "Fuenf" };

    hashtable.insert(storage.data(), storage.data() + 5);

    for (auto& e : hashtable) {
        std::cout << "Hash entry: " << e.key << " -> " << e.value << "\n";
    }

    std::cout << "hashtable[\"three\"] -> " << hashtable.find({"three"})->value << "\n";
}
