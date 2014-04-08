#include <type_traits>
#include <utility>

namespace meta {
template <typename T>
using Unqual = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
}

template <typename T, typename U>
typename std::enable_if<std::is_base_of<meta::Unqual<T>, meta::Unqual<U>>::value, T>::type private_up_cast(U&& u) {
    return (T)std::forward<U>(u);
}

struct a { int x; };
struct b { int x; };
struct c { int x; };

struct foo : private b {};
struct bar : public a, private b {};

int main() {
    foo one;
    bar two;
    auto&& one_b = private_up_cast<b&>(one);
    auto&& two_b = private_up_cast<b&>(two);

    // fails
    //auto&& two_c = private_up_cast<c&>(two);
}
