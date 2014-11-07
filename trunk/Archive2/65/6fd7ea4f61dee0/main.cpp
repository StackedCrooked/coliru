#include <iostream>
#include <type_traits>

namespace detail {
    namespace swap_tests {
        // if swap ADL finds this it would call std::swap otherwise
        struct tag {};
        template<class T> tag swap(T&, T&) noexcept(
            std::is_nothrow_move_constructible<T>::value &&
            std::is_nothrow_move_assignable<T>::value
        );

        template<class T, std::size_t N>
        tag swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)));

        template<class, class> std::false_type uses_std(...);
        template<class T, class U>
        std::is_same<decltype(swap(std::declval<T&>(), std::declval<U&>())), tag> uses_std(int);

        template<class, class> std::false_type can_swap(...);
        template<class T, class U, class = decltype(swap(std::declval<T&>(), std::declval<U&>()))>
        std::true_type can_swap(int);
    }
}

template<class T, class U>
struct is_swappable : std::integral_constant<bool, 
    decltype(detail::swap_tests::can_swap<T, U>(0))::value &&
        (!decltype(detail::swap_tests::uses_std<T, U>(0))::value ||
            (std::is_move_assignable<T>::value && std::is_move_constructible<T>::value))
> {};

template<class T, std::size_t N>
struct is_swappable<T[N], T[N]> : std::integral_constant<bool, 
    decltype(detail::swap_tests::can_swap<T[N], T[N]>(0))::value &&
        (!decltype(detail::swap_tests::uses_std<T[N], T[N]>(0))::value || is_swappable<T, T>::value)
> {};


struct A {
    A(A&&) = delete;
};

struct B {
    B(B&&) = delete;
};

void swap(B&, B&);

int main() {
    std::cout << is_swappable<int, int>() << "\n";
    std::cout << is_swappable<A, A>() << "\n";
    std::cout << is_swappable<B, B>() << "\n";
    std::cout << is_swappable<int[42], int[42]>() << "\n";
    std::cout << is_swappable<A[42], A[42]>() << "\n";
    std::cout << is_swappable<B[42], B[42]>() << "\n";

}