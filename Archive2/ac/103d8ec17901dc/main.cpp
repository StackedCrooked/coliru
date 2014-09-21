#include <type_traits>
namespace details {
    template<class T, T value>
    struct number_sink {};
    template<class T>
    struct check_mult_helper {
        template<T U, T V>
        static std::true_type test(number_sink<T, U*V> *);
        template<T U, T V>
        static std::false_type test(...);
    };
}

template<class T, T U, T V>
using check_multiply = decltype(details::check_mult_helper<T>::template test<U, V>(nullptr));

int main(){
    static_assert(!check_multiply<int, 60000, 60000>(), "Oops");
    static_assert(check_multiply<long, 60000, 60000>(), "Oops");
    static_assert(check_multiply<int, 6000, 6000>(), "Oops");
}