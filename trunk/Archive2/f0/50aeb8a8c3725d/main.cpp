#include <utility>

struct plus {
    template<typename Lhs, typename Rhs>
    constexpr auto operator()(Lhs&& lhs, Rhs&& rhs) const
    -> decltype( std::forward<Lhs>(lhs) + std::forward<Rhs>(rhs) )
    { return std::forward<Lhs>(lhs) + std::forward<Rhs>(rhs); }
} constexpr plus_object {};

int main(int argc, char**)
{
    return plus_object(argc, argc);
}