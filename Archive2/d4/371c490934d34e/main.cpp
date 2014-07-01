#include <vector>
#include <iostream>

template<typename T>
std::vector<T>
conv(std::vector<T> const &f, std::vector<T> const &g) {
  int const nf = f.size();
  int const ng = g.size();
  int const n  = nf + ng - 1;
  std::vector<T> out(n, T());
  for(auto i(0); i < n; ++i) {
    int const jmn = (i >= ng - 1)? i - (ng - 1) : 0;
    int const jmx = (i <  nf - 1)? i            : nf - 1;
    for(auto j(jmn); j <= jmx; ++j) {
      out[i] += (f[j] * g[i - j]);
    }
  }
  return out; 
}

int main() {
    std::vector<double> f{0.2, 0.5, -0.4, 1.0, 0.0};
    std::vector<double> g{0.6, 1.9, -2.2};
    
    auto v1 = conv(f, g);
    for(auto i : v1) std::cout << i << " ";
    std::cout << std::endl;
    
    auto v2 = conv(g, f);
    for(auto i : v2) std::cout << i << " ";
    std::cout << std::endl;
}