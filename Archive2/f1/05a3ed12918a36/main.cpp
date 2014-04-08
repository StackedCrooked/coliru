#include <type_traits>
#include <utility>

namespace meta {
template <typename C, typename T, typename E>
using If = typename std::conditional<C::value, T, E>::type;

template <typename T>
using UnqualNoPointer = typename std::remove_cv<typename std::remove_reference<typename std::remove_pointer<T>::type>::type>::type;

template <typename T>
using RemoveReference = typename std::remove_reference<T>::type;

template <typename T>
using RemovePointer = typename std::remove_pointer<T>::type;

template <typename T>
using RemoveReferenceOrPointer = If<std::is_pointer<T>, RemovePointer<T>, RemoveReference<T>>;

template <typename T, typename U>
struct is_more_cv : std::integral_constant<bool,
    (!std::is_const<RemoveReferenceOrPointer<U>>::value || std::is_const<RemoveReferenceOrPointer<T>>::value)
 && (!std::is_volatile<RemoveReferenceOrPointer<U>>::value || std::is_volatile<RemoveReferenceOrPointer<T>>::value)> {};
}

template <typename T, typename U>
typename std::enable_if<std::is_base_of<meta::UnqualNoPointer<T>, meta::UnqualNoPointer<U>>::value && meta::is_more_cv<T, U>::value, T>::type private_up_cast(U&& u) {
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
    //auto&& p_two_cb = private_up_cast<b const*>(two);
    auto p_two_cvb = private_up_cast<b const volatile*>(&two);

    // fails
    //auto&& two_c = private_up_cast<c&>(two);
}
