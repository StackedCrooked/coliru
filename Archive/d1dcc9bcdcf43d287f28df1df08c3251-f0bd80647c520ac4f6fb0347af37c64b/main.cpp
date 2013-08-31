#include <type_traits>
#include <vector>
#include <memory>

template <typename T>
class HasEmplace
{
  typedef char yes;
  struct no { char dummy[2]; };
  template <typename U, void (U::*)(const typename T::value_type&)> struct Check;
  template <typename U> static yes test(Check<U, &U::emplace>*);
  template <typename U> static no test(...);
public:
  static constexpr bool value = (sizeof(test<T>(0)) == sizeof(yes));
};

static_assert(HasEmplace<std::vector<int>>::value, "");

int main() {}
