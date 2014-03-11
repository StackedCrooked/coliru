#include <vector>
#include <iostream>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/proto/traits.hpp>
#include <cstdlib>

struct Record {
    char const* data;
};

typedef boost::unordered_map<std::string, std::vector<Record*> > MAP;

struct OuterRelation
{
    short num_keys;
    short join_key_ndx;
    MAP hash_table;
};

template <typename T, typename... Args>
T* make_memory_leak(Args&&... args) {
    static_assert(std::is_pod<T>::value, "undefined behaviour for non-POD types");

    T* raw = static_cast<T*>(malloc(sizeof(T)));

    static_assert(boost::proto::is_aggregate<T>::value, "aggregate initialization required");
    *raw = { std::forward<Args>(args)... };

    return raw;
}

int main()
{
    auto outer_relation = std::make_shared<OuterRelation>();
    for (auto key : { "some string", "some other string", "which", "by the way", "are", "const char(&)[]" })
        outer_relation->hash_table[key].push_back(make_memory_leak<Record>(key));

    /* print all keys in the hash table */
    BOOST_FOREACH(MAP::value_type pair, outer_relation->hash_table)
    {
        std::cout << pair.first << "\n";
    }
}
