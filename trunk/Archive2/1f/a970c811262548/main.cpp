#include <boost/range/adaptors.hpp>
#include <vector>
#include <utility>
#include <iostream>
#include <iterator>

using namespace boost::adaptors;

using container_type = std::vector<std::pair<bool,int>>;

struct to_include {
  bool operator()(const std::pair<bool,int>& x) {
    return x.first;
  }
};

int main() {
  container_type container;

  /* element0: 1, 1 */
  /* element1: 1, 2 */
  /* element2: 1, 3 */
  for(size_t i=0; i!=3; ++i) container.push_back(std::make_pair(true, i+1));
  container_type container_cpy = container;

  /* filter and then reverse */
  auto fr = container | filtered(to_include()) | reversed;
  auto fr_it1 = container.begin();
  auto fr_it2 = std::next(fr_it1);
  fr_it2->first = false;

  std::cout << "FILTER AND THEN REVERSE\n";
  std::cout << fr_it2->first << " " << fr_it2->second << '\n'; /* prints (1,1) instead of (0,2) */

  /* reverse and then filter */
  auto rf = container_cpy | reversed | filtered(to_include());
  auto rf_it1 = container_cpy.begin();
  auto rf_it2 = std::next(rf_it1);
  rf_it2->first = false;

  std::cout << "\nREVERSE AND THEN FILTER\n";
  std::cout << rf_it2->first << " " << rf_it2->second << '\n'; /* prints (0,2) */

  return 0;
}