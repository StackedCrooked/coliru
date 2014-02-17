#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <stack>
#include <type_traits>
#include <vector>

template <bool B, typename T>
using enable_if =
  typename std::enable_if<B, T>::type;

template <typename T>
struct is_sequence_helper {
  template <typename U=T>
  static auto test(int) ->
    enable_if<
      std::is_same<
        decltype(std::declval<U>().begin()),
        decltype(std::declval<U>().end())
      >::value,
      std::true_type
    >;

  template <typename U=T>
  static auto test(...) -> std::false_type;
};

template <typename T>
using is_sequence =
  decltype(is_sequence_helper<T>::test(0));

template <typename T>
struct is_stack_helper {
  template <typename U=T>
  static auto test(int) ->
    decltype((std::declval<U>().top(),
              std::declval<U>().pop(),
              std::declval<const U>().empty(),
              std::true_type{}));
  
  template <typename U=T>
  static auto test(...) -> std::false_type;
};
template <typename T>
using is_stack =
  decltype(is_stack_helper<T>::test(0));

template<typename Sequence>
enable_if<
  is_sequence<Sequence>::value &&
    !is_stack<Sequence>::value,
  std::ostream&
> operator<<(std::ostream& os, const Sequence& cont)
{
    os << "sequence version:\n";
    for (const auto& el : cont)
        std::cout << el << '\n';
    return os;
}

template<typename Stack>
enable_if<
  is_stack<Stack>::value,
  std::ostream&
> operator<<(std::ostream& os, Stack& cont)
{
    os << "stack version:\n";
    for (; !cont.empty(); cont.pop())
        std::cout << cont.top() << '\n';
    return os;
}

int main() {
    auto integers = {0,1,2,3};
    std::vector<int> vec = integers;
    std::stack<int> stk;
    for (auto i : integers) stk.push(i);
    std::list<int> lst = integers;
    
    std::cout << vec;
    std::cout << stk;
    std::cout << lst;
}
