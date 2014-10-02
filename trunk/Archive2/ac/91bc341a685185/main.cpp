#include "concepts.hpp"

namespace concepts {
    
template<typename Val> constexpr Val const& as_const(Val& val) noexcept { return val; }

using namespace Concepts::Toolkit;

template<typename Type>
struct Booly {
    template<typename X>
    auto requires(X const& x) -> expr<decltype( x ), explicit_<bool>>;
};

} // concepts

namespace conparts {

using namespace Concepts::Toolkit;
using namespace concepts;

template<typename L, typename R>
struct EqualTo {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> expr<decltype( as_const(x) == as_const(y) ), models<Booly>>;
};

template<typename L, typename R>
struct NotEqualTo {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> expr<decltype( as_const(x) != as_const(y) ), models<Booly>>;
};

template<typename L, typename R>
struct LessThan {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> expr<decltype( as_const(x) < as_const(y) ), models<Booly>>;
};

template<typename L, typename R>
struct GreaterThan {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> expr<decltype( as_const(x) > as_const(y) ), models<Booly>>;
};

template<typename L, typename R>
struct LessEqual {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> expr<decltype( as_const(x) <= as_const(y) ), models<Booly>>;
};

template<typename L, typename R>
struct GreaterEqual {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> expr<decltype( as_const(x) >= as_const(y) ), models<Booly>>;
};

} // conparts

namespace concepts {

namespace parts = conparts;

template<typename Left, typename Right = Left>
struct EqualityComparable {
    template<typename X, typename Y = X>
    auto requires(X&& x, Y&& y = std::declval<X>()) -> nested<
        parts::EqualTo<X, Y>,
        parts::NotEqualTo<X, Y>
    >;
};

template<typename Left, typename Right = Left>
struct Comparable {
    template<typename X, typename Y = X>
    auto requires(X&& x, Y&& y = std::declval<X>()) -> nested<
        EqualityComparable<Left, Right>,
        parts::LessThan<Left, Right>,
        parts::LessEqual<Left, Right>,
        parts::GreaterThan<Left, Right>,
        parts::GreaterEqual<Left, Right>
    >;
};

} // concepts

template<
    typename T, typename U
    // Bad Clang!
    // , Concepts::Requires<concepts::Comparable<T, U>>...
    , typename = Concepts::Requires<concepts::Comparable<T, U>>
>
bool constrained_function(T const& a, U const& b)
{ return a < b; }

struct inty { inty(bool); explicit operator int() const { return 0; } };
struct dummy {};

bool operator==(dummy const&, dummy const&) { return true; }
// uh oh
inty operator!=(dummy const&, dummy const&) { return true; }
bool operator<(dummy const&, dummy const&) { return true; }
bool operator>(dummy const&, dummy const&) { return true; }
bool operator<=(dummy const&, dummy const&) { return true; }
bool operator>=(dummy const&, dummy const&) { return {}; }

int main()
{
    constrained_function(Concepts::diagnostic(dummy {}), dummy {});
    // constrained_function(dummy {}, dummy {});
}