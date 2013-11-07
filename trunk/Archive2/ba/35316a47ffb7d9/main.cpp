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
}

namespace std
{
    template<typename T, typename U>
    struct hash<pair<T, U>>
    {
        size_t operator()(const pair<T,U>& v) const
        {
            return ( 39 * make_hash(v.first) ) ^ make_hash(v.second);
        }
    };

    template<typename... T>
    struct hash<vector<T...>>
    {
        size_t operator()(const vector<T...>& v) const
        {
            size_t result = 0;
            for( auto& e : v ) {
                result *= 39;
                result ^= make_hash(e);
            }
            return result;
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
