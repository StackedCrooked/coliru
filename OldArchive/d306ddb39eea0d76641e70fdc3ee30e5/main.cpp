#include <cstddef>
#include <type_traits>

namespace my {
template <typename T, std::size_t I>
struct indexed {};
}

template <std::size_t N, typename T>
T find_with_index_impl(my::indexed<T, N> const&);

template <typename... T>
struct inherit_all : T... {};

template <std::size_t N, typename... T>
using find_with_index = decltype(find_with_index_impl<N>(inherit_all<T...>()));

static_assert(std::is_same<
        find_with_index<42, my::indexed<int, 23>, my::indexed<double, 42>, my::indexed<float, 17>>,
        double>::value, "this should work");

int main() {}