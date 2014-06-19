#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <type_traits>

template <typename T> struct container_traits {
  static bool const value = false;  
};

template <typename... Args>
struct container_traits<std::vector<Args...>> {
  static bool const value = true;
};

template <typename... Args>
struct container_traits<std::deque<Args...>> {
  static bool const value = true;
};

template <typename... Args>
struct container_traits<std::list<Args...>> {
  static bool const value = true;
};

template <typename... Args>
struct container_traits<std::set<Args...>> {
  static bool const value = true;
};

template <typename... Args>
struct container_traits<std::map<Args...>> {
  static bool const value = true;
};

template <typename... Args>
struct container_traits<std::unordered_set<Args...>> {
  static bool const value = true;
};

template <typename... Args>
struct container_traits<std::unordered_map<Args...>> {
  static bool const value = true;
};

template<typename T>
struct is_std {
    static constexpr bool const value = container_traits<T>::value;
};

auto main() -> int {
  std::vector<int> v;
  std::cout << std::boolalpha << is_std<decltype(v)>::value << std::endl;
  std::deque<int> dq;
  std::cout << std::boolalpha << is_std<decltype(dq)>::value << std::endl;
  std::set<int> s;
  std::cout << std::boolalpha << is_std<decltype(s)>::value << std::endl;
  std::map<int, int> m;
  std::cout << std::boolalpha << is_std<decltype(m)>::value << std::endl;
  std::unordered_set<int> us;
  std::cout << std::boolalpha << is_std<decltype(us)>::value << std::endl;
  std::unordered_map<int, int> um;
  std::cout << std::boolalpha << is_std<decltype(um)>::value << std::endl;
  std::list<int> l;
  std::cout << std::boolalpha << is_std<decltype(l)>::value << std::endl;
  int i;
  std::cout << std::boolalpha << is_std<decltype(i)>::value << std::endl;
  double d;
  std::cout << std::boolalpha << is_std<decltype(d)>::value << std::endl;

  return 0;
}