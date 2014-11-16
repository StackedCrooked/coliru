#include <ext/hash_map>
#include <iostream>

using namespace std;

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
    __gnu_cxx::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace __gnu_cxx
{
    template<typename S, typename T> struct hash<pair<S, T>>
    {
        inline size_t operator()(const pair<S, T> & v) const
        {
            size_t seed = 0;
            ::hash_combine(seed, v.first);
            ::hash_combine(seed, v.second);
            cout << "hash value: " << seed << endl;
            return seed;
        }
    };
}

int main(){
    __gnu_cxx::hash_map<pair<int, int>, int> hm;
    hm[make_pair(1,2)] = 3;
}
