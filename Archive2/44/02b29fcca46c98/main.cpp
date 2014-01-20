#include <type_traits>

#define SELF \
  static auto self_helper_() -> decltype(*this); \
  using self = typename std::decay<decltype(self_helper_())>::type

struct foo {
  SELF;
};

static_assert(std::is_same<foo,foo::self>(),"BOOM!");
