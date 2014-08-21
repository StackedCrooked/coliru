#include <iostream>
#include <map>


template<typename Map>
struct KeyIterator
{
    typedef typename Map::iterator iterator;
    typedef typename Map::key_type value_type;
    
    KeyIterator(iterator it) : it(it) {}
    
    value_type operator*()
    {
        return it->first;
    }
    
    KeyIterator& operator++()
    {
        ++it;
        return *this;
    }
    
    friend bool operator==(KeyIterator a, KeyIterator b)
    {
        return a.it == b.it;
    }
    
    friend bool operator!=(KeyIterator a, KeyIterator b)
    {
        return a.it != b.it;
    }
    
    iterator it;
};


template<typename Map>
struct ValueIterator
{
    typedef typename Map::iterator iterator;
    typedef typename Map::mapped_type value_type;
    
    ValueIterator(iterator it) : it(it) {}
    
    value_type operator*()
    {
        return it->second;
    }
    
    ValueIterator& operator++()
    {
        ++it;
        return *this;
    }
    
    friend bool operator==(ValueIterator a, ValueIterator b)
    {
        return a.it == b.it;
    }
    
    friend bool operator!=(ValueIterator a, ValueIterator b)
    {
        return a.it != b.it;
    }
    
    iterator it;
};

          


template<typename Map>
KeyIterator<Map> key_begin(Map& map)
{
    return { map.begin() };
}


template<typename Map>
KeyIterator<Map> key_end(Map& map)
{
    return { map.end() };
}

template<typename Map>
ValueIterator<Map> values_begin(Map& map)
{
    return { map.begin() };
}


template<typename Map>
ValueIterator<Map> values_end(Map& map)
{
    return { map.end() };
}


template<typename It>
struct IteratorRange
{
    IteratorRange(It b, It e) : b(b), e(e) {}
    
    It begin() { return b; }
    It end() { return e; }
    
    It b, e;
};


template<typename Map>
IteratorRange<KeyIterator<Map>> keys(Map& map)
{
    return { key_begin(map), key_end(map) };
}


template<typename Map>
IteratorRange<ValueIterator<Map>> values(Map& map)
{
    return { values_begin(map), values_end(map) };
}


template<typename It>
IteratorRange<It> range(It b, It e)
{
    return { b, e };
}


int main()
{
    std::map<int, std::string> map = {
        { 1, "one" },
        { 2, "two" },
        { 3, "three" }
    };


    for (auto&& i : keys(map))
    {
        std::cout << i << ' ';
    }
    
    std::cout << std::endl;
    
    for (auto&& i : values(map))
    {
        std::cout << i << ' ';
    }
}

