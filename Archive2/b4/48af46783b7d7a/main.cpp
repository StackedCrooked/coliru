// next_permutation example
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>



int main () {
  std::vector<std::pair<int, int>> v {{3, 600}, {2, 900}, {2, 800}};

  std::sort (v.begin(), v.end());

  std::cout << "The 3! possible permutations with 3 elements:\n";
  do {
    std::cout << "(" << v[0].first << ',' << v[0].second << "), " << " (" << v[1].first << ',' << v[1].second <<"), "
              << "(" << v[2].first << ',' << v[2].second << ")." << '\n';
  } while ( std::next_permutation(v.begin(), v.end()) );

  return 0;
}