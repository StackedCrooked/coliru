#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

struct in_tag {
  template<class T>
  struct in_oper {
    template<class U>
    bool operator> (U const& data) {
      using std::begin;
      using std::end;

      return std::find (begin (data), end (data), value) != end (data);
    }

    T const& value;
  };

  template<class T>
  friend in_oper<T> operator< (T const& value, in_tag) {
    return { value };
  }
} in;


int main () {
  std::vector<int> vec {1,2,3};

  std::cout << (2 <in> vec) << std::endl;
  std::cout << (0 <in> vec) << std::endl;
}