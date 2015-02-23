#include <utility>
#include <functional>

namespace std
{
 
template<typename T, typename U>
struct hash<std::pair<T, U>>
{
public:
    std::size_t operator () (std::pair<T, U> const& p) const
    {
        return std::hash<T>{}(p.first) ^ std::hash<U>{}(p.second);
    }
};

}

#include <unordered_set>
#include <iostream>

enum class E
{
    a,
    b
};

namespace std
{

template<>
struct hash<E>
{
public:
    std::size_t operator () (E e) const
    {
        return std::hash<int>{}(static_cast<int>(e));
    }
};

}

int main() 
{
    auto s = std::unordered_set<std::pair<int, E>>{};
    
    s.insert({42, E::a});
    s.insert({1337, E::b});
    s.insert({42, E::a});
    
    for (auto x : s)
    {
        std::cout << "(" << x.first << ", " << static_cast<int>(x.second) << ") ";
    }
}

