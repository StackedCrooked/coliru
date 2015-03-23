#include <vector>
#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include <boost/intrusive/unordered_set.hpp>

namespace bic = boost::intrusive;

std::hash<std::string> hash_fn;

struct MyClass : bic::unordered_set_base_hook<bic::link_mode<bic::auto_unlink>>
{
    std::string name;
    int anInt1;
    mutable bool bIsMarkedToDelete;

    MyClass(std::string name, int i) : name(name), anInt1(i), bIsMarkedToDelete(false) {}

    bool operator==(MyClass const& o) const
    {
        return anInt1 == o.anInt1 && name == o.name;
    }

    struct hasher
    {
        size_t operator()(MyClass const& o) const
        {
            return hash_fn(o.name);
        }
    };
};

std::ostream& operator << (std::ostream& out, const MyClass& ac) {
    return out << ac.name << " " << ac.anInt1;
}

typedef bic::unordered_set<MyClass, bic::hash<MyClass::hasher>, bic::constant_time_size<false> > HashTable;

template <typename HT>
void debug_buckets(HT const& hashtable) {
    std::multimap<size_t, MyClass const*> debug_map;
    std::transform(hashtable.begin(), hashtable.end(), 
            std::inserter(debug_map, debug_map.end()), 
            [&](MyClass const& mc) { return std::make_pair(hashtable.bucket(mc), &mc); }
        );

    std::cout << "\nDebugging buckets of hashtable\n";
    for (auto& entry : debug_map)
        std::cout << "Debug bucket: " << entry.first << " -> " << *entry.second << "\n";
}

int main()
{
    std::vector<MyClass> values {
        MyClass { "Dagobart", 25 },
        MyClass { "Dagobart", 26 },
        MyClass { "Dagobart", 27 },
        MyClass { "John",     0  },
        MyClass { "John",     10 },
        MyClass { "John",     15 },
        MyClass { "John",     5  },
        MyClass { "Mike",     0  },
        MyClass { "Mike",     25 },
        MyClass { "Mike",     25 },
        MyClass { "Mike",     27 }
    };

    HashTable::bucket_type buckets[100];
    HashTable hashtable(values.begin(), values.end(), HashTable::bucket_traits(buckets, 100));

    debug_buckets(hashtable);

    std::cout << "Removing all Mikes\n";
    values.erase(
            std::remove_if(values.begin(), values.end(), [](MyClass const& mc) { return mc.name == "Mike"; }),
            values.end());

    debug_buckets(hashtable);
}
