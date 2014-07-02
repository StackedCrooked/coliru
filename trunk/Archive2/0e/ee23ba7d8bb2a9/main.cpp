#include <vector>
#include <iostream>

template<typename T>
std::vector<T>
conv_valid(std::vector<T> const &f, std::vector<T> const &g) {
  int const nf = f.size();
  int const ng = g.size();
  std::vector<T> const &min_v = (nf < ng)? f : g;
  std::vector<T> const &max_v = (nf < ng)? g : f;
  int const n  = std::max(nf, ng) - std::min(nf, ng) + 1;
  std::vector<T> out(n, T());
  for(auto i(0); i < n; ++i) {
    for(int j(min_v.size() - 1), k(i); j >= 0; --j) {
      out[i] += min_v[j] * max_v[k];
      ++k;
    }
  }
  return out;
}

int main() {
    std::vector<int> f{3, 1, 4, -1, 2};
    std::vector<int> g{-1, 1, 2};
       
    auto v1 = conv_valid(f, g);
    for(auto i : v1) std::cout << i << " ";
    std::cout << std::endl;
    
    auto v2 = conv_valid(g, f);
    for(auto i : v2) std::cout << i << " ";
    std::cout << std::endl;
}