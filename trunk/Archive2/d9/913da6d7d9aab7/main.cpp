#include <iostream>

namespace detail {
  // No copy constructor. Move constructor not deleted if T has one.
  template <typename T>
  struct Test : T { Test(Test&&) = default; };
}

// TODO: Implement unions
template <typename T>
using is_moveable = std::is_move_constructible<
    std::conditional_t<std::is_class<T>{}, detail::Test<T>, T>>;

class Moveable {};
class NotMoveable {NotMoveable(NotMoveable const&); }; // No move constructor

static_assert( is_moveable<Moveable>::value, "" );
static_assert( !is_moveable<NotMoveable>::value, "" );
static_assert( is_moveable<int>::value, "" );
static_assert( !is_moveable<void>::value, "" );

int main() {}