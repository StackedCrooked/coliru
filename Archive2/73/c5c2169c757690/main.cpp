#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <type_traits>

struct stdcontainer_tag { };
struct nonstdcontainer_tag { };

template <typename T> struct container_traits {
  typedef nonstdcontainer_tag category;  
};

template <typename... Args>
struct container_traits<std::vector<Args...>> {
  typedef stdcontainer_tag category;
};

template <typename... Args>
struct container_traits<std::list<Args...>> {
  typedef stdcontainer_tag category;
};

template <typename... Args>
struct container_traits<std::set<Args...>> {
  typedef stdcontainer_tag category;
};

template <typename... Args>
struct container_traits<std::map<Args...>> {
  typedef stdcontainer_tag category;
};

template<typename T>
struct is_std {
    static constexpr const bool value = !std::is_same<typename container_traits<T>::category, nonstdcontainer_tag>::value;
};

auto main() -> int {
  std::vector<int> v;
  std::cout << std::boolalpha << is_std<decltype(v)>::value << std::endl;
  std::set<int> s;
  std::cout << std::boolalpha << is_std<decltype(s)>::value << std::endl;
  std::map<int, int> m;
  std::cout << std::boolalpha << is_std<decltype(m)>::value << std::endl;
  std::list<int> l;
  std::cout << std::boolalpha << is_std<decltype(l)>::value << std::endl;
  int i;
  std::cout << std::boolalpha << is_std<decltype(i)>::value << std::endl;
  double d;
  std::cout << std::boolalpha << is_std<decltype(d)>::value << std::endl;

  return 0;
}