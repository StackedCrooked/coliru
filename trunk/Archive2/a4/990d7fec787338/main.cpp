#include <iostream>
#include <string>
#include <map>

template<typename Tmap>
struct myPair
{
    typedef typename Tmap::value_type::first_type key_type;
    typedef typename Tmap::value_type::second_type value_type;
    
    key_type key;
    value_type value;
    
    myPair(const typename Tmap::iterator &i)
        : key(i->first), value(i->second)
    {
    }
};

int main()
{
    typedef typename std::map<short, std::string> TestMap;
    TestMap someMap;
    
    someMap.insert(TestMap::value_type(123, "Hello"));
    someMap.insert(TestMap::value_type(456, "World"));
    
    for (auto i = someMap.begin(), e = someMap.end(); i != e; ++i) {
        myPair<TestMap> keyval(i);
        std::cout << "key=" << keyval.key << " value=" << keyval.value << std::endl;
    }
}

