#include <iostream>
#include <iterator>
#include <vector>
#include <list>

namespace detail {
  template<class It>
  void func (It, std::random_access_iterator_tag) {
    std::cerr << "random-access\n";
  }

  template<class It>
  void func (It, std::forward_iterator_tag) {
    std::cerr << "forward\n";
  }
}

template<class It, class ItCat = typename std::iterator_traits<It>::iterator_category>
auto func (It x) -> decltype (detail::func (x, ItCat {})) {
  return detail::func (x, ItCat {});
}

int main () {
  func (std::  list<int>::iterator {});
  func (std::vector<int>::iterator {});
}