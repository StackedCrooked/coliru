#include <iterator>
#include <list>

template<class T, class Allocator, class Predicate>
typename std::list<T, Allocator>::iterator
list_partition(std::list<T, Allocator>& list, Predicate predicate) {
  auto first = list.begin();
  auto last = list.end();

  for (;;) {
    for (; first != last && predicate(*first); ++first) {}
    for (; first != last && !predicate(*std::prev(last)); --last) {}
    if (first == last) {
      return first;
    }

    auto next = std::next(first);
    auto prev = std::prev(last);
    list.splice(last, list, first);
    list.splice(next, list, prev);
    last = first;
    first = next;
  }
}

template<class T, class Allocator, class Predicate>
typename std::list<T, Allocator>::iterator
stable_list_partition(std::list<T, Allocator>& list, Predicate predicate) {
  auto first = list.begin();
  auto partition_point = list.end();
  for (;;) {
    if (first == partition_point) return first;
    if (!predicate(*first)) break;
    ++first;
  }
  partition_point = first;

  if (std::next(first) == list.end()) return first;

  for(;;) {
    auto next = std::next(first);
    list.splice(list.end(), list, first);
    first = next;
    for (;;) {
      if (first == partition_point) return first;
      if (!predicate(*first)) break;
      ++first;
    }
  }
}

#include <initializer_list>
#include <iostream>

struct even_predicate {
  template <typename T>
  bool operator () (const T& t) const {
    return t % 2 == 0;
  }
};

void test_one(std::initializer_list<int> il) {
  std::list<int> lst = il;
  std::cout << "Before: ";
  auto os = std::ostream_iterator<int>(std::cout, " ");
  std::copy(lst.begin(), lst.end(), os);
  std::cout << '\n';
  auto partition_point = stable_list_partition(lst, even_predicate{});
  std::cout << "Evens: ";
  std::copy(lst.begin(), partition_point, os);
  std::cout << "\nOdds: ";
  std::copy(partition_point, lst.end(), os);
  std::cout << '\n';
}

int main() {
  test_one({});
  test_one({0});
  test_one({1});
  test_one({0,1,2,3,4,5,6,7,8,9});
  test_one({1,3,5,7,9,0,2,4,6,8});
}
