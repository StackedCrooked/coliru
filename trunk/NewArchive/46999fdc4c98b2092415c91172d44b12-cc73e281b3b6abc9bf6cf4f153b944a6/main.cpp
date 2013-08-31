#include <algorithm>
#include <iostream>
#include <vector>

namespace a {
  struct b {
      friend void swap(b&, b&) {}
  };  
  struct c {};  
  void swap(c&, c&) {}
}

template <typename T>
void (*get_swap())(T&, T&) {
    return [](T& x, T& y) { return swap(x, y); };
}

int main() {

    //auto f0 = (void (*)(a::b&, a::b&)) a::swap; //error: ‘swap’ is not a member of ‘a’
    auto f1 = get_swap<a::b>();
    auto f2 = get_swap<a::c>();
    auto f3 = get_swap<std::vector<int>>();

    std::cout << std::hex;
    //std::cout << (unsigned long long) f0 << '\n';
    std::cout << (unsigned long long) f1 << '\n';
}