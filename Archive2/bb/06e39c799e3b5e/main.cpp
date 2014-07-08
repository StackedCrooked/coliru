#include <vector>

template<class X> class Y{};

template<template<class outer, class... x> class inner, template<class element, class... x> class outer, class element, class... x>
inner<outer<element, x...>, x...> my_function(const outer<inner<element>>& var, int cnt) {
  inner<outer<element, x...>, x...> ret;
  (void)var, (void)cnt;
  return ret;
}

int main() {
#if 1
    const std::vector<std::vector<int>> x;
#else
    const Y<Y<int>> x{};
#endif
    my_function(x, 0);
}