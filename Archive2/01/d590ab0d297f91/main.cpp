#include <iterator>
#include <type_traits>
#include <vector>
#include <iostream>

template<typename T>
  struct container
{
  container (size_t count, const T& init) {std::cout << "first\n"; }
  template <typename InputIt,
            typename = typename std::enable_if<not std::is_integral<InputIt>::value
  and std::is_base_of
    <std::input_iterator_tag
    ,typename std::iterator_traits<InputIt>::iterator_category
    >::value>::type >
    container (InputIt first,InputIt last) {std::cout << "second\n"; }
};

typedef container<int> int_cont;

int main()
{ std::vector<int> v (5,3);
  int_cont a1 (3,6); // first constructor
  int_cont a2 (3u,6); // first constructor
  int_cont a3 (3,6u); // first constructor
  int_cont a4 (3u,6u); // first constructor
  int_cont b(v.begin(),v.end()); // second constructor
}
