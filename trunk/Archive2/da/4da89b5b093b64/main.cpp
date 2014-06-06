#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <limits>
#include <climits>
#include <tuple>

using namespace std;

struct Widget {
  int id = 1;
};

template<typename T>
auto foo(T &&t) -> decltype(std::get<0>(std::forward<T>(t))) { return std::get<0>(t); }

Widget w;
auto list = std::make_tuple(w, Widget());

auto main() -> int {
  std::cout << "[by value] before: " << std::get<0>(list).id << std::endl;
  auto w0 = foo(list);
  w0.id = 2;
  std::cout << "[by value list] after : " << std::get<0>(list).id << std::endl;
  std::cout << "[by value w0]   after : " << w0.id << std::endl << std::endl << std::endl;

  std::cout << "[&] before: " << std::get<0>(list).id << std::endl;
  auto &w1 = foo(list);
  w1.id = 3;
  std::cout << "[&] after : " << std::get<0>(list).id << std::endl << std::endl;

  std::cout << "[&&] before: " << std::get<0>(list).id << std::endl;
  auto &&w2 = foo(list);
  w2.id = 4;
  std::cout << "[&&] after : " << std::get<0>(list).id << std::endl << std::endl;

  std::cout << std::boolalpha << std::is_rvalue_reference<decltype(foo(std::make_tuple(w, Widget())))>::value << std::endl;

  return 0;
}