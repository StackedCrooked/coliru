#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>

namespace
{
    template<typename T>
    std::size_t make_hash(const T& v)
    {
        return std::hash<T>()(v);
    }
    
    void hash_combine(std::size_t& h, const std::size_t& v)
    {
        h ^= v + 0x9e3779b9 + (h << 6) + (h >> 2);
    }

    template<typename T>
    struct hash_container
    {
        size_t operator()(const T& v) const
        {
            size_t h=0;
            for( const auto& e : v ) {
                hash_combine(h, make_hash(e));
            }
            return h;
        }
    };
}

namespace std
{
    template<typename T, typename U>
    struct hash<pair<T, U>>
    {
        size_t operator()(const pair<T,U>& v) const
        {
            size_t h=make_hash(v.first);
            hash_combine(h, make_hash(v.second));
            return h;
        }
    };

    template<typename... T>
    struct hash<vector<T...>> : hash_container<vector<T...>> {};

    template<typename... T>
    struct hash<map<T...>> : hash_container<map<T...>> {};
}

int main()
{
    std::unordered_set<std::vector<std::pair<int,int>>> us;
    us.insert(std::vector<std::pair<int,int>>{{{42,0},{17,64}}});
    std::cout << us.size() << std::endl;
    std::cout << us.begin()->size() << std::endl;
    std::cout << us.begin()->begin()->first << std::endl;

    std::unordered_set<std::map<int,int>> usm;
    std::map<int,int> m{{42,0},{17,64}};
    usm.insert(m);
}
