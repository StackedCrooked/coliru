#include <type_traits>
#include <string>
#include <memory> 

template <class... Args0toN>
struct areCopyConstructible;

template<>
struct areCopyConstructible<> : std::true_type {};

template <class Arg0, class... Args1toN, class std::enable_if< !std::is_copy_constructible<Arg0>::value>::type* = nullptr >
struct areCopyConstructible : std::false_type {};

template <class Arg0, class... Args1toN, class std::enable_if< std::is_copy_constructible<Arg0>::value>::type* = nullptr >
struct areCopyConstructible : areCopyConstructible<Args1toN...> {};

int main()
{
  static_assert(areCopyConstructible<>::value, "failed");
  static_assert(areCopyConstructible<int>::value, "failed");
  static_assert(areCopyConstructible<int, std::string>::value, "failed");
  static_assert(!areCopyConstructible<std::unique_ptr<int> >::value, "failed");
  static_assert(!areCopyConstructible<int, std::unique_ptr<int> >::value, "failed");
  static_assert(!areCopyConstructible<std::unique_ptr<int>, int >::value, "failed");
}