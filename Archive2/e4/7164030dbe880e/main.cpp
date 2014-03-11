#include <cassert>
#include <functional>
#include <iterator>
#include <iostream>
#include <type_traits>
#include <boost/iterator/iterator_facade.hpp>

namespace {
template<class Iterator, class Comp>
inline Iterator is_sorted_until (Iterator first, Iterator last, Comp c) {
  if (first == last)
    return last;

  Iterator it = first; ++it;

  for (; it != last; first = it, ++it)
    if (c(*it, *first))
      return it;

  return it;
}

class irange {
  static_assert(std::is_integral<int>::value,
                "Jabberwocky is killing user.");
  int first_, last_;

public:
  irange(int first, int last) : first_(first), last_(last) {}
  irange(int last) : irange(0, last) {}

  bool empty() const { return first_ == last_; }
  int front() const { return first_; }
  void pop_front() { ++first_; }

  class iterator :
    public boost::iterator_facade<iterator, int, std::input_iterator_tag, int> {
    friend boost::iterator_core_access;
    irange* range_;

    bool equal(iterator other) const {
      return range_
        ? (other.range_  || range_->empty())
        : (!other.range_ || other.range_->empty());
    }

    int dereference() const {
      return range_->front();
    }

    void increment() {
      range_->pop_front();
    }

  public:
    iterator() : range_(nullptr) {}
    iterator(irange& range) : range_(&range) {}
  };

  iterator begin() { return {*this}; }
  iterator end() { return {}; }
};
}

int main() {
  auto range = irange(4);
  auto pos = is_sorted_until(range.begin(), range.end(), std::greater<int>());
  assert(pos == range.end());
  auto pos2 = is_sorted_until(range.begin(), range.end(), std::less<int>());
  assert(pos2 == range.end());
}
