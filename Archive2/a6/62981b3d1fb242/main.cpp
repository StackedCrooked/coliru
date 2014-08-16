#include <iostream>
#include <iterator>
#include <algorithm>
#include <type_traits>

template<typename BidirIt, typename BinaryPredicate>
void equivalence_partition(BidirIt first, BidirIt last, BinaryPredicate p) {
  using element_type = typename std::decay<decltype(*first)>::type;
    
  if(first == last) {
    return;
  }

  auto new_first = std::partition
    (first, last, [=](element_type const &rhs) { return p(*first, rhs); });

  equivalence_partition(new_first, last, p);
}

template<typename BidirIt>
void equivalence_partition(BidirIt first, BidirIt last) {
  using element_type = typename std::decay<decltype(*first)>::type;
  equivalence_partition(first, last, std::equal_to<element_type>());
}

int main() {
  auto foo = std::vector<int> { 1, 2, 1, 3, 1, 2 };
  equivalence_partition(foo.begin(), foo.end());
  std::copy(foo.begin(), foo.end(), std::ostream_iterator<int>(std::cout, " "));
}