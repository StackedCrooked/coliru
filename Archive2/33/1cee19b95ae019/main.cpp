#include <tuple>
#include <iostream>

template <class T>
constexpr size_t value_size() { return sizeof(T); }

template <class... Args>
class CalcArgsSize;

template <class Arg, class... Args>
class CalcArgsSize<Arg, Args...> {
 public:
  static const size_t result = value_size<Arg>() + CalcArgsSize<Args...>::result;
};

template <>
class CalcArgsSize<> {
 public:
  static const size_t result = 0;
};

int main() {
  std::cout << CalcArgsSize<bool, int, long>::result << std::endl;
  return EXIT_SUCCESS;
}