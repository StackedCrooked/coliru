#include <iostream>
#include <cstddef>
#include <map>
#include <utility>

namespace my{
template<class T>
struct internal_key{
    using type = typename T::key_type const;
    internal_key(type* k) : key(k){}
    internal_key(type& k) : key(&k){}
    
    struct comparator{
        bool operator()(internal_key const& left, internal_key const& right) const{
            return *left.key < *right.key;
        }
    };
    
    mutable type* key;
};
    
template<class V>
using internal_map = std::map<internal_key<V>, V, typename internal_key<V>::comparator>;

template<class InternalMap, class T, class KeyView>
std::pair<typename InternalMap::iterator, bool> insert(InternalMap& map, T&& v, KeyView&& kv){
    auto itp = map.emplace(kv(v), std::forward<T>(v));
    if(itp.second)
        itp.first->first.key = &kv(itp.first->second);
    return itp;
}
} // my::

struct mystruct {
    using key_type = std::string;
    std::string key;
  
    int myfield;
    // lots of stuff
};

int main()
{
    auto key_view = [](mystruct const& v) -> std::string const&{ return v.key; }; // = [].key;
    my::internal_map<mystruct> map;
    my::insert(map, mystruct{"abc", 0}, key_view);
    my::insert(map, mystruct{"def", 20}, key_view);
    my::insert(map, mystruct{"ghi", 42}, key_view);
    
    std::cout << map.size() << "\n";
    for(auto&& p : map)
        std::cout << *p.first.key << ":" << p.second.key << "\n";
        
    std::cout << map[std::string("abc")].myfield << '\n';
    std::cout << map[std::string("def")].myfield << '\n';
    std::cout << map[std::string("ghi")].myfield << '\n';
}
