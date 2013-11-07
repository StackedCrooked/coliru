#include <iostream>
#include <string>
#include <vector>
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
    struct hash<vector<T...>>
    {
        size_t operator()(const vector<T...>& v) const
        {
            size_t h=0;
            for( auto& e : v ) {
                hash_combine(h, make_hash(e));
            }
            return h;
        }
    };
}

int main()
{
    std::unordered_set<std::vector<std::pair<int,int>>> us;
    us.insert(std::vector<std::pair<int,int>>{{{42,0},{17,64}}});
    std::cout << us.size() << std::endl;
    std::cout << us.begin()->size() << std::endl;
    std::cout << us.begin()->begin()->first << std::endl;
}
