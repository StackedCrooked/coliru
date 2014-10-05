#include <iostream>
#include <type_traits>

namespace detail {
    template<class T, class U, bool = std::is_signed<T>::value, bool = std::is_signed<U>::value>
    struct less_helper;

    template<class T, class U, bool same_sign> struct less_helper<T, U, same_sign, same_sign> {
        static constexpr bool less(T x, U y) { return x < y; }
    };

    template<class T, class U> struct less_helper<T, U, true, false> {
        static constexpr bool less(T x, U y) {
            return x < 0 || static_cast<typename std::make_unsigned<T>::type>(x) < y;
        }
    };

    template<class T, class U> struct less_helper<T, U, false, true> {
        static constexpr bool less(T x, U y) {
            return y > 0 && x < static_cast<typename std::make_unsigned<U>::type>(y);
        }
    };
}

template<class T, class U>
inline constexpr bool less(T x, U y) {
    return detail::less_helper<T, U>::less(x, y);
}

int main(int argc, char** argv) {
    std::cout << less(1, 2u) << "\n";
    return 0;
}
