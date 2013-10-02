#include <algorithm>
#include <iostream>
#include <vector>

struct X {
  int n;
  X(int v) : n(v) {}
};


void print(const std::vector<X>& container) {
    for (const auto& value : container) {
        std::cout << value.n << " ";
    }
    std::cout << "\n";
}

int main() {
    
  std::vector<X> v{5, 4, 6};
  print(v);
  std::sort(v.begin(), v.end(), [](const X& a, const X& b){ return a.n < b.n; });
  print(v);
}