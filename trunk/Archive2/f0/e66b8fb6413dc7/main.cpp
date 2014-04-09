#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/range/adaptors.hpp>

using namespace std;

// Return a range of iterators to the elements
// of the given range.
template <typename Range>
auto make_index(Range& range)
  -> vector<decltype(range.begin())> {
  vector<decltype(range.begin())> index;
  for (auto i = begin(range), e = end(range); i != e; ++i) {
    index.push_back(i);
  }
  return index;
}

int main() {
  map<string, map<int,int>> tokens = {
    {"A", {{1, 1}, {2, 2}}},
    {"a", {{3, 1}}},
    {"an", {{2, 1}}},
    {"And", {{4, 1}}},
    {"and", {{3, 1}}}
  };
  
  auto index = make_index(tokens);
  using iterator = decltype(tokens.begin());
  sort(begin(index), end(index), [](iterator a, iterator b){
    // Boost's case-insensitive string compare
    return boost::algorithm::ilexicographical_compare(a->first, b->first);
  });

  cout << "Sorted:\n";
  for (auto&& i : index | boost::adaptors::indirected) {
    cout << i.first << ':';
    for (auto const& j : i.second) {
      cout << ' ' << j.first << ':' << j.second;
    }
    cout << '\n';
  }
}
