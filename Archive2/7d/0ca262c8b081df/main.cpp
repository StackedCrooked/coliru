#include <iostream>
#include <string>
#include <map>

template<typename Tmap>
struct OCDMapIter
{
    typedef typename Tmap::iterator map_iterator;
    typedef typename Tmap::value_type::first_type key_type;
    typedef typename Tmap::value_type::second_type value_type;
    
    map_iterator iter;
    
    OCDMapIter(const map_iterator &i)
        : iter(i)
    {
    }
    
    const key_type &key() const
    {
        return iter->first;
    }
    
    value_type &value()
    {
        return iter->second;
    }
};

int main()
{
    typedef typename std::map<short, std::string> TestMap;
    TestMap someMap;
    
    someMap.insert(TestMap::value_type(123, "Hello"));
    someMap.insert(TestMap::value_type(456, "World"));
    
    for (auto i = someMap.begin(), e = someMap.end(); i != e; ++i) {
        OCDMapIter<TestMap> keyval(i);
        keyval.value() += " modified";
        std::cout << "key=" << keyval.key() << " value=" << keyval.value() << std::endl;
    }
}

