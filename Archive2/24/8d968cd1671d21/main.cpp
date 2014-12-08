#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <limits>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <tuple>

template<typename Key, typename Value, typename String = std::string, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
class AttributeMgr
{
    using index_t = std::uint32_t;
    using value_pair = std::pair < index_t, Value > ;
    using attribute_map_t = std::unordered_multimap < Key, value_pair, Hash, KeyEqual >;
    using hasher = typename attribute_map_t::hasher;
    using key_equal = typename attribute_map_t::key_equal;
    using iterator = typename attribute_map_t::iterator;
    using const_iterator = typename attribute_map_t::const_iterator;
    using local_iterator = typename attribute_map_t::local_iterator;
    using const_local_iterator = typename attribute_map_t::const_local_iterator;
    using size_type = typename attribute_map_t::size_type;
    using key_type = typename attribute_map_t::key_type;
    using value_type = std::tuple<Key, String, Value>;
    using mapped_type = typename attribute_map_t::mapped_type;

    std::unordered_map<String, index_t> string_map;
    std::vector<String> strings;
    attribute_map_t attributes;

    // exceptions
    struct overflow_error : public std::overflow_error
    {
        overflow_error() : std::overflow_error("AttributeMgr: overflow") {}
    };
    struct out_of_range : public std::out_of_range
    {
        out_of_range(index_t index)
            : std::out_of_range("AttributeMgr: index is out of bounds: "
            + std::to_string(index))
        {
        }
    };
    struct invalid_key : public std::runtime_error
    {
        invalid_key() : std::runtime_error("AttributeMgr: invalid key") {}
    };

    //-------------------------------------------------------------------------
    // find_index: get index of the name in the string_map
    //-------------------------------------------------------------------------
    index_t find_index(const String& name) const
    {
        auto i = string_map.find(name);
        return i != string_map.end() ? i->second : 0;
    }

    //-------------------------------------------------------------------------
    // create_index: insert the name to the string_map, return index
    //-------------------------------------------------------------------------
    index_t create_index(const String& name)
    {
        if(strings.size() + 1 > std::numeric_limits<index_t>::max())
        {
            throw overflow_error{};
        }
        strings.push_back(name);
        auto index = static_cast<index_t>(strings.size());
        string_map[name] = index;
        return index;
    }

public:
    // constructors
    AttributeMgr() = default;

    explicit AttributeMgr(size_type bucket_count,
        const Hash& hash = Hash(),
        const KeyEqual& equal = KeyEqual())
        : attributes(bucket_count, hash, equal)
    {
    }

    AttributeMgr(const AttributeMgr& other) = default;
    
    AttributeMgr(AttributeMgr&& other) 
        : string_map(std::move(other.string_map)), 
        strings(std::move(other.strings)),
        attributes(std::move(other.attributes)) 
    {
    }
    
    // assigments
    AttributeMgr& operator=(const AttributeMgr&) = default;
    
    AttributeMgr& operator=(AttributeMgr&& other)
    {
        string_map = std::move(other.string_map);
        strings = std::move(other.strings);
        attributes = std::move(other.attributes);
    }

    // iterators
    const_iterator cbegin() const { return attributes.begin(); }
    const_iterator cend() const { return attributes.end(); }
    const_iterator begin() const { return attributes.begin(); }
    const_iterator end() const { return attributes.end(); }
    iterator begin() { return attributes.begin(); }
    iterator end() { return attributes.end(); }

    // Capacity
    bool empty() const { return attributes.empty(); }
    size_type size() const { return attributes.size(); }
    size_type max_size() const { return attributes.max_size(); }
    
    // Modifiers
    void clear() { attributes.clear(); }
    template<class P>
    iterator insert(const key_type& key, const String& name, P&& value)
    { 
        return try_emplace(key, name, std::forward<P>(value)).first;
    }

    iterator insert(const value_type& value)
    {
        return try_emplace(std::get<0>(value), 
            std::get<1>(value), std::get<2>(value)).first;
    }

    template<class K, class... Args>
    std::pair<iterator, bool> try_emplace(K&& key, const String& name, Args&&... args)
    {
        if(auto index = find_index(name))
        {
            auto it_range = attributes.equal_range(key);
            for(auto it = it_range.first; it != it_range.second; ++it)
            {
                if(it->second.first == index)
                    return{ it, false };
            }

            auto it = attributes.emplace_hint(it_range.second,
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(key)),
                std::forward_as_tuple(index, Value(std::forward<Args>(args)...)));

            return{ it, true };
        }
        else
        {
            index = create_index(name);
            auto it = attributes.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(std::forward<K>(key)),
                std::forward_as_tuple(index, Value(std::forward<Args>(args)...)));

            return{ it, true };
        }
    }

    template <class K, class M>
    std::pair<iterator, bool> insert_or_assign(K&& key, const String& name, M&& obj)
    {
        auto result = try_emplace(std::forward<K>(key), name, std::forward<M>(obj));
        if(!result.second)
        {
            auto it = result.first;
            it->second.second = std::forward<M>(obj);
        }
        return result;
    }

    iterator erase(const_iterator position)
    {
        return attributes.erase(position);
    }
    size_type erase(const key_type& x, const String& name)
    {
        auto it = find(x, name);
        if(it != attributes.end())
        {
            attributes.erase(it);
            return 1;
        }
        return 0;
    }
    size_type erase(const key_type& x) { return attributes.erase(x); }
    iterator erase(const_iterator first, const_iterator last)
    {
        return attributes.erase(first, last);
    }
    
    void swap(const key_type& key1, const key_type& key2)
    {
        if(attributes.key_eq()(key1, key2))
            return;

        auto move_data_out = [this](const key_type& key)
        {
            auto range = attributes.equal_range(key);
            std::vector<value_pair> tmp;
            for(auto it = range.first; it != range.second; ++it)
            {
                tmp.emplace_back( it->second.first,
                    std::move(it->second.second) );
            }
            attributes.erase(range.first, range.second);
            return tmp;
        };

        auto data1 = move_data_out(key1);
        auto data2 = move_data_out(key2);

        for(auto&& d : data1)
        {
            attributes.emplace(key2, std::move(d));
        }
        for(auto&& d : data2)
        {
            attributes.emplace(key1, std::move(d));
        }
    }

    void swap(const key_type& key1, const String& name1, const key_type& key2, const String& name2)
    {
        if(attributes.key_eq()(key1, key2) && name1 == name2)
            return;
        auto it1 = find(key1, name1);
        if(it1 != attributes.end())
        {
            auto it2 = find(key2, name2);
            if(it2 != attributes.end())
            {
                std::swap(it1->second.second, it2->second.second);
            }
            else
            {
                insert_or_assign(key2, name2, std::move(it1->second.second));
                erase(key1, name1);
            }
        }
        else
        {
            auto it2 = find(key2, name2);
            if(it2 != attributes.end())
            {
                insert_or_assign(key1, name1, std::move(it2->second.second));
                erase(key2, name2);
            }
        }
    }
    // Lookup
    size_type count(const Key& key) const { return attributes.count(key); }
    size_type count(const Key& key, const String& name) const;
    iterator find(const Key& key) { return attributes.find(key); }
    const_iterator find(const Key& key) const { return attributes.find(key); }
    iterator find(const Key& key, const String& name) 
    { 
        if(auto index = find_index(name))
        {
            auto it_range = attributes.equal_range(key);
            for(auto it = it_range.first; it != it_range.second; ++it)
            {
                if(it->second.first == index)
                    return it;
            }
        }
        return attributes.end();
    }
    const_iterator find(const Key& key, const String& name) const 
    { 
        if(auto index = find_index(name))
        {
            auto it_range = attributes.equal_range(key);
            for(auto it = it_range.first; it != it_range.second; ++it)
            {
                if(it->second.first == index)
                    return it;
            }
        }
        return attributes.end();
    }
    std::pair<iterator, iterator> equal_range(const Key& key) { return attributes.equal_range(key); }
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return attributes.equal_range(key);
    }

    Value& at(const key_type& key, const String& name)
    {
        auto it = find(key, name);
        if(it != attributes.end())
            return it->second.second;
        else
            throw invalid_key{};
    }
    const Value& at(const key_type& key, const String& name) const
    {
        auto it = find(key, name);
        if(it != attributes.end())
            return it->second.second;
        else
            throw invalid_key{};
    }

    // Bucket interface
    local_iterator begin(size_type n) { return attributes.begin(n); }
    const_local_iterator begin(size_type n) const { return attributes.begin(n); }
    const_local_iterator cbegin(size_type n) const { return attributes.begin(n); }

    local_iterator end(size_type n) { return attributes.end(n); }
    const_local_iterator end(size_type n) const { return attributes.end(n); }
    const_local_iterator cend(size_type n) const { return attributes.end(n); }

    size_type bucket_count() const { return attributes.bucket_count(); }
    size_type max_bucket_count() const { return attributes.max_bucket_count(); }
    size_type bucket_size(size_type n) const { return attributes.bucket_size(); }
    size_type bucket(const Key& key) const { return attributes.bucket(key); }

    // Hash policy
    float load_factor() const { return attributes.load_factor(); }
    float max_load_factor() const { return attributes.max_load_factor(); }
    void max_load_factor(float ml) { attributes.max_load_factor(ml); }
    void rehash(size_type count) { attributes.rehash(count); }
    void reserve(size_type count) { attributes.reserve(count); }

    // Observers
    hasher hash_function() const { return attributes.hash_function(); }
    key_equal key_eq() const { return attributes.key_eq(); }

    // String interface
    //-------------------------------------------------------------------------
    // get a string value from index
    //-------------------------------------------------------------------------
    const String& get_string(index_t index) const
    {
        if(--index < strings.size())
        {
            return strings[index];
        }
        else
        {
            throw out_of_range{ index };
        }
    }

};

int main(int argc, char* argv[])
{
    AttributeMgr<void*, unsigned, std::string> amgr;
    int k = 0;
    unsigned v = 0;
    amgr.try_emplace(&k, "name", v);
    amgr.insert_or_assign(&k, "name", v + 1);
    amgr.insert_or_assign(&k, "name1", v + 2);
    amgr.insert_or_assign(&k, "name2", v + 3);

    auto dump = [&]()
    {
        for(auto&& a : amgr)
        {
            std::cout << a.first << ": " << a.second.first << " (" << amgr.get_string(a.second.first) << "): "
                << a.second.second << "\n";
        }
    };

    dump();

    int k2 = 0;
    amgr.erase(&k, "name1");
    amgr.insert(&k, "name2", 123);
    amgr.insert(std::make_tuple( &k, "name3", 333));
    amgr.insert(std::forward_as_tuple(&k, "name4", 444));
    amgr.insert(&k2, "k2-name", 0);
    amgr.insert(&k2, "k2-name1", 111);
    std::cout << "name1 erased, name2 inserted again, name3 inserted, name4 inserted, k2 name and name1 inserted\n";
    dump();

    amgr.swap(&k, &k2);
    std::cout << "k and k2 have been swapped\n";
    dump();

    amgr.swap(&k2, "name", &k2, "name2");
    std::cout << "k name and k name2 have been swapped\n";
    dump();

    amgr.swap(&k2, "name", &k, "k2-name");
    std::cout << "k2 name and k k2-name2 have been swapped\n";
    dump();

    amgr.swap(&k2, "name", &k2, "noname");
    std::cout << "k name and k noname have been swapped\n";
    dump();

    return 0;
}
