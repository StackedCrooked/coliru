#include <iostream>

namespace detail {
    template <typename T>
    struct Test : T { Test(Test&&) = default; };
}

// TODO: Implement unions
template <typename T>
using is_moveable = std::integral_constant<bool, 
    std::conditional_t<std::is_class<T>{}, 
       std::is_constructible<detail::Test<T>, detail::Test<T>>, std::is_arithmetic<T>>::value>;

class Moveable {};
class NotMoveable {NotMoveable(NotMoveable const&); }; // No move constructor

static_assert( is_moveable<Moveable>::value, "" );
static_assert( !is_moveable<NotMoveable>::value, "" );
static_assert( is_moveable<int>::value, "" );
static_assert( !is_moveable<void>::value, "" );

int main() {}