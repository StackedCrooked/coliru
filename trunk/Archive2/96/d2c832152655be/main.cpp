#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>

int main() {
  std::string a = "working";
  std::string b = "soaked";

  sort(begin(a), end(a));
  a.erase(unique(begin(a), end(a)), end(a));

  sort(begin(b), end(b));
  b.erase(unique(begin(b), end(b)), end(b));

  set_intersection(begin(a), end(a), begin(b), end(b), std::ostream_iterator<char>(std::cout, ""));
}
