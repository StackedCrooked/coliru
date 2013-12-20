#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

template <typename LInput, typename RInput, typename Output>
Output merge_elements(LInput lbegin, LInput lend,
                      RInput rbegin, RInput rend,
                      Output out) {
    while(true) {
        if (lbegin == lend) {
            return std::copy(rbegin, rend, out);
        }

        if (rbegin == rend) {
            return std::copy(lbegin, lend, out);
        }
        
        if (lbegin->first < rbegin->first) {
            *out++ = *lbegin++;
        } else if (rbegin->first < lbegin->first) {
            *out++ = *rbegin++;
        } else {
            *out++ = std::make_pair(lbegin->first, lbegin->second + rbegin->second);
            ++lbegin;
            ++rbegin;
        }
    }
}

/* Convenience type alias for our element. */
using Elem = std::pair<int, double>;

/* Convenience type alias for the container of our elements. */
using Elems = std::vector<Elem>;

int main() {
  // Sample data.
  Elems lhs {{1, 2.3}, {2, 3}, {5, 3.4}};
  Elems rhs {{1, 1.3}, {3, 5.5}, {4, 2.2}};
  Elems result;
  // Merge and use appender to append elements.
  merge_elements(std::begin(lhs),
                 std::end(lhs),
                 std::begin(rhs),
                 std::end(rhs),
                 std::back_inserter(result));
  // Print result.
  for (const auto &elem : result) {
    std::cout << elem.first << ' ' << elem.second << std::endl;
  }  // for
}
