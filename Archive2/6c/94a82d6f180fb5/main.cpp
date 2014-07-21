#include <set>
#include <iostream>
#include <iterator>
#include <utility>
#include <type_traits>

using namespace std;

namespace My {
    // base case
    using std::to_string;

    // overload for strings
    template <typename Char, typename Traits, typename Alloc>
    std::basic_string<Char, Traits, Alloc>
    to_string(std::basic_string<Char, Traits, Alloc> s) {
        return s;
    }

    // overload for iterators
    template<typename Iterator>
    auto to_string(Iterator i) -> decltype(to_string(*i)) {
        return "iterator to: \"" + to_string(*i) + '"';
    }
}

int main() {
  int i = 2;
  string str = "Hello";
  set<int> s;
  s.insert(i);
  cout << My::to_string(i) << ", " << str << ", "
       << My::to_string(s.begin()) << ", " << My::to_string(&i) << endl;
}