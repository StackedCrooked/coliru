#include <iostream>
#include <vector>
#include <map>
#include <type_traits>
#include <iterator>

using namespace std;

template <class, class Enable = void> struct is_iterator : std::false_type {};
template <typename T> struct is_iterator<T, typename std::enable_if<std::is_pointer<typename std::iterator_traits<T>::pointer>::value>::type> : std::true_type {};

namespace detail {
  template<typename T1, typename T2>
  std::ostream& print_elem(std::ostream &out, std::pair<T1, T2> const &mp) {
    return (out << "(" << mp.first << ", " << mp.second << ")");
  }
  
  template<typename T>
  std::ostream& print_elem(std::ostream &out, T const &elem, typename std::enable_if<!is_iterator<T>::value>::type* = nullptr) {
    return (out << elem);
  }

  template<typename T>
  std::ostream& print_elem(std::ostream &out, T const &elem, typename std::enable_if<is_iterator<T>::value>::type* = nullptr) {
    return print_elem(out, *elem);
  }
}

template<typename Iterator>
void print(Iterator begin, Iterator end)
{
  while (begin != end) {
    detail::print_elem(cout, begin) << endl;
    ++begin;
  }
}

int main() {
  vector<int> noVec = { 1, 2, 3 };
  print(noVec.begin(), noVec.end());
  map<int, int> nosMap;
  nosMap[0] = 1;
  nosMap[1] = 2;
  nosMap[3] = 3;
  print(nosMap.begin(), nosMap.end());

  return 0;
}