#include <vector>
#include <iostream>

template<typename Container>
struct enumerate_iterator {
  typename Container::size_type i;
  typename Container::iterator v;

  bool operator!=(enumerate_iterator const &rhs) { return i != rhs.i; }
  enumerate_iterator &operator++() {
    ++i;
    ++v;
    return *this;
  }
  enumerate_iterator &operator*() { return *this; }
};

template <typename Container> struct enumerate_impl {
  Container c;

  auto begin() {
    return enumerate_iterator<Container>{0, c.begin()};
  }
  auto end() {
    return enumerate_iterator<Container>{c.size(), c.end()};
  }
};

template <typename Container> struct enumerate_impl<Container &> {
  Container &c;

  auto begin() {
    return enumerate_iterator<Container>{0, c.begin()};
  }
  auto end() {
    return enumerate_iterator<Container>{c.size(), c.end()};
  }
};

template <typename Container>
enumerate_impl<Container> enumerate(Container &c) {
  return {c};
}

template <typename Container> enumerate_impl<Container> enumerate(Container &&c) {
  return {c};
}

int main() {
  for (auto &&iv : enumerate(std::vector<int>{2, 3, 5, 7, 11, 13, 17})) {
    std::cout << iv.i << ' ' << *(iv.v) << '\n';
  }
  
  std::vector<int> x{0,0,0,0,0,0,0,0};
  for (auto &&iv : enumerate(x)) {
      *(iv.v) = iv.i;
      std::cout << *(iv.v) << '\n';
  }
}
