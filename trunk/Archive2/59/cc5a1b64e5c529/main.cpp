#include <algorithm>
#include <iostream>
#include <vector>

/* Convenience type alias for our element. */
using Elem = std::pair<int, double>;

/* Convenience type alias for the container of our elements. */
using Elems = std::vector<Elem>;

template<class InputIt1, class InputIt2, class OutputIt, 
         class OrderingPred, class EqualityPred, class Combiner>
OutputIt merge_special( InputIt1 first1, InputIt1 last1,
                        InputIt2 first2, InputIt2 last2,
                        OutputIt d_first, OrderingPred comp, 
                        EqualityPred eq, Combiner comb )
{
    for (; first1 != last1; ++d_first) {
        if (first2 == last2) {
            return std::copy(first1, last1, d_first);
        }
        if (comp(*first2, *first1)) {
            *d_first = *first2;
            ++first2;
        } else if (eq(*first2, *first1)) {
            *d_first = comb(*first2, *first1);
            ++first1; ++first2;
        } else {
            *d_first = *first1;
            ++first1;
        }
    }
    return std::copy(first2, last2, d_first);
}

int main() {
  // Sample data.
  Elems lhs {{1, 2.3}, {2, 3}, {5, 3.4}};
  Elems rhs {{1, 1.3}, {3, 5.5}, {4, 2.2}};
  Elems result;
  // Merge and use appender to append elements.
  merge_special(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs),
                std::back_inserter(result), 
                [](Elem const& l, Elem const& r) { return l.first < r.first; },
                [](Elem const& l, Elem const& r) { return l.first == r.first; },
                [](Elem const& l, Elem const& r) { 
                    Elem result = l; 
                    result.second += r.second; 
                    return result;
                });
  // Print result.
  for (const auto &elem : result) {
    std::cout << elem.first << ' ' << elem.second << std::endl;
  }  // for
}
