#include <iostream>
#include <functional>
#include <utility>
#include <unordered_set>

template<typename T>
void
hash_combine(std::size_t &seed, T const &key) {
  std::hash<T> hasher;
  seed ^= hasher(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
  template<typename T1, typename T2>
  struct hash<std::pair<T1, T2>> {
    std::size_t operator()(std::pair<T1, T2> const &p) const {
      std::size_t seed1(0);
      ::hash_combine(seed1, p.first);
      ::hash_combine(seed1, p.second);

      std::size_t seed2(0);
      ::hash_combine(seed2, p.first);
      ::hash_combine(seed2, p.second);

      return std::min(seed1, seed2);
    }
  };
}

int main() {
    std::unordered_set<std::pair<int, int>> s;
    std::pair<int, int> a = std::make_pair(4, 3);
    s.insert(a);
    std::pair<int, int> b = std::make_pair(2, 1);
    s.insert(b);
    std::pair<int, int> c = std::make_pair(5, 6);
    s.insert(c);
    std::pair<int, int> d = std::make_pair(1, 2);
    s.insert(d);
    for(auto e : s) std::cout << e.first << ", " << e.second << std::endl; 
    
    return 0;
}