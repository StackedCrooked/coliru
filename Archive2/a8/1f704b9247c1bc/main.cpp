#include <type_traits>
#include <utility>

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

#include <iostream>

template<typename Sequence>
enable_if<
  is_sequence<Sequence>::value && !is_stack<Sequence>::value,
  std::ostream&
> operator<<(std::ostream& os, const Sequence& cont) {
  os << "sequence version:\n";
  for (const auto& el : cont)
    os << el << '\n';
  return os;
}

template<typename Stack>
enable_if<
  is_stack<Stack>::value,
  std::ostream&
> operator<<(std::ostream& os, Stack& cont) {
  os << "stack version:\n";
  for (; !cont.empty(); cont.pop())
    os << cont.top() << '\n';
  return os;
}

#include <array>
#include <deque>
#include <forward_list>
#include <initializer_list>
#include <list>
#include <stack>
#include <vector>

class my_sequence {
  std::vector<int> storage_;
public:
  my_sequence(std::initializer_list<int> il) : storage_(il) {}
  const int* begin() const { return &storage_[0]; }
  const int* end() const { return &storage_[0] + storage_.size(); }
};

class my_stack {
  std::vector<int> storage_;
public:
  bool empty() const { return storage_.empty(); }
  int& top() { return storage_.back(); }
  void pop() { storage_.pop_back(); }
  void push(int i) { storage_.push_back(i); }
};

int main() {
  // Sequences:
  std::cout << std::array<int, 4>{0,1,2,3};
  std::cout << std::deque<int>{0,1,2,3};
  std::cout << std::forward_list<int>{0,1,2,3};
  std::cout << std::list<int>{0,1,2,3};
  std::cout << std::vector<int>{0,1,2,3};

  // Stack:
  std::stack<int> stk;
  for (auto i : {0,1,2,3})
    stk.push(i);
  std::cout << stk;

  // Non-standard library types:
  std::cout << my_sequence{0,1,2,3};
  my_stack mstk;
  for (auto i : {0,1,2,3})
    mstk.push(i);
  std::cout << mstk;
}
