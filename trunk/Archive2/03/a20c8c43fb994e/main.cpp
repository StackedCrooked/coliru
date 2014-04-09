#include <type_traits>
#include <utility>

namespace meta {
template <typename T>
using Unqual = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
template <typename T>
using RemoveReference = typename std::remove_reference<T>::type;

// volatile left as an exercise for the reader
template <typename T, typename U>
struct is_more_const : std::integral_constant<bool, !std::is_const<RemoveReference<U>>::value || std::is_const<RemoveReference<T>>::value> {};
}

template <typename T, typename U>
typename std::enable_if<std::is_base_of<meta::Unqual<T>, meta::Unqual<U>>::value && meta::is_more_const<T, U>::value, T>::type private_up_cast(U&& u) {
    return (T)std::forward<U>(u);
}

struct a { int x; };
struct b { int x; };
struct c { int x; };

struct foo : private b {};
struct bar : public a, private b {};

int main() {
    foo one;
    bar const two = {};
    auto&& one_b = private_up_cast<b&>(one);
    // fails
    //auto&& two_b = private_up_cast<b&>(two);
    auto&& two_cb = private_up_cast<b const&>(two);

    // fails
    //auto&& two_c = private_up_cast<c&>(two);
}
