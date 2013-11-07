#include <type_traits>
#include <cstddef>

namespace wheels {
    namespace meta {
        namespace detail {
            struct nothrow_placement_tag {};
        } // namespace detail
    } // namespace meta
} // namespace wheels

void* operator new(std::size_t, wheels::meta::detail::nothrow_placement_tag) noexcept;

namespace wheels {
    namespace meta {
        template <typename T, typename... Args>
        struct is_nothrow_placeable : std::integral_constant<bool, noexcept(new(detail::nothrow_placement_tag{}) T(std::declval<Args>()...))> {};
    } // namespace meta
} // namespace wheels


int main() {
    static_assert(wheels::meta::is_nothrow_placeable<int>(), "I win");
}
