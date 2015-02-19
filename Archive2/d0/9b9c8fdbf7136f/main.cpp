#include <vector>
#include <iostream>

template <typename Container>
void print(const Container &C) {
  for (const auto &Elem : C) {
    std::cout << Elem << " ";
  }
  std::cout << std::endl;
}

void f() {
  std::vector<int> v0(10, 2);
  std::vector<int> v1{10, 2, 5};
  std::vector<int> v2{10, 2};
  std::vector<int> v3{10};
  std::vector<int> v4(10);
  
  print(v0);
  print(v1);
  print(v2);
  print(v3);
  print(v4);
}

int main() {
  f();
}