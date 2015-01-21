#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class S {
  int Data1, Data2;
  
public:
  S(int D1, int D2) : Data1(D1), Data2(D2) {}
  
  friend bool operator<(const S& lhs, const S& rhs) {
    return std::tie(lhs.Data1, lhs.Data2) < std::tie(rhs.Data1, rhs.Data2); 
  }
  
  friend std::ostream& operator<<(std::ostream &OS, const S &D) {
    OS << D.Data1 << ", " << D.Data2;
    return OS;
  }
};

void f() {
  std::vector<std::unique_ptr<S>> vi;
  vi.emplace_back(std::make_unique<S>(12, 24));
  vi.emplace_back(std::make_unique<S>(100, 5));
  vi.emplace_back(std::make_unique<S>(5, 82));
  vi.emplace_back(std::make_unique<S>(97, 1));
  std::sort(vi.begin(), vi.end());
  for (const auto &i : vi) {
    std::cout << *i << std::endl;
  }
}

int main() {
  f();   
}