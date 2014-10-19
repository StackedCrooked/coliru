#include <utility>

struct plus {
    template<typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs&& lhs, Rhs&& rhs) const
    -> decltype( std::forward<Lhs>(lhs) + std::forward<Rhs>(rhs) )
    { return std::forward<Lhs>(lhs) + std::forward<Rhs>(rhs); }
} constexpr plus_object {};

template<typename Functor, typename Arg>
struct bound {
    Functor functor;
    Arg arg;
    
    template<typename... Rest>
    constexpr auto operator()(Rest&&... rest)
    -> decltype( (*functor)(arg, std::forward<Rest>(rest)...) )
    { return (*functor)(arg, std::forward<Rest>(rest)...); }
};

int main(int argc, char**)
{
    return bound<decltype(plus_object)*, int> { &plus_object, argc }(argc);
}