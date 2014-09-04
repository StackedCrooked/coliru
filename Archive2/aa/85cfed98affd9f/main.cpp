#include <iterator>
#include <type_traits>
#include <vector>

template <typename I>
  struct input_iter : public std::integral_constant<bool,
  not std::is_integral<I>::value
  and std::is_base_of
    <std::input_iterator_tag
    ,typename std::iterator_traits<I>::iterator_category
    >::value >
  {};

template<typename T>
  struct container
{
  container (size_t count, const T& init);
  template <typename InputIt,
            typename = typename std::enable_if<input_iter<InputIt>::value> >
    container (InputIt first,InputIt last);
};

typedef container<int> int_cont;

void f()
{ std::vector<int> v (5,3);
  int_cont a1 (3u,6); // first constructor
  int_cont a2 (3u,6); // first constructor
  int_cont a3 (3,6); // first constructor
  int_cont a4 (3,6); // first constructor
  int_cont a5 (3,6); // first constructor
  int_cont b(v.begin(),v.end()); // second constructor
}
