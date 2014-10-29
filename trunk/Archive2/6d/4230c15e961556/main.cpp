#include <cstddef>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>

namespace detail {
    template<class F, class ...T, class = decltype(std::declval<F>()(std::declval<T>()...))> 
    std::true_type callable_test(F, T...);
    std::false_type callable_test(...);

    template<class F, class ...T> 
    using callable_with = decltype(callable_test(std::declval<F>(), std::declval<T>()...));

    template<class T>
    struct ImplicitConvertGet {
        template<class U>
        typename std::enable_if<std::is_convertible<const U&, T>::value, T>::type
        operator()(const U& u) { return u; }
    };

    template<class T, class Func, class Tuple, std::size_t N,
             bool = callable_with<Func, typename std::tuple_element<N, Tuple>::type>::value>
    struct SafeGet {
        static T get(const Tuple& tuple) {
            throw std::invalid_argument("dynamic_get called with bad type at the requested index");
        }
    };

    template<class T, class Func, class Tuple, std::size_t N>
    struct SafeGet<T, Func, Tuple, N, true> {
        static T get(const Tuple& tuple) { return Func()(std::get<N>(tuple)); }
    };

    template<class T, class Tuple, std::size_t N=0, std::size_t M=std::tuple_size<Tuple>::value>
    struct DynamicGetHelper {
        template<class Func>
        static T get(std::size_t index, const Tuple& tuple, const Func& func) {
            if (index == N) return SafeGet<T, Func, Tuple, N>::get(tuple);
            return DynamicGetHelper<T, Tuple, N+1, M>::get(index, tuple, func);
        }
    };

    template<class T, class Tuple, std::size_t M>
    struct DynamicGetHelper<T, Tuple, M, M> {
        template<class Func>
        static T get(std::size_t index, const Tuple& tuple, const Func& func) {
            throw std::out_of_range("index out of range");
        }
    };
}

// dynamic_get<T>(index, tuple) returns the std::get<index>(tuple) if it is trivially convertible
// to T, or throws a std::invalid_argument otherwise. std::out_of_range is thrown when the index is
// out of bounds of the tuple.
template<class T, class Tuple>
T dynamic_get(std::size_t index, const Tuple& tuple) {
    return detail::DynamicGetHelper<T, Tuple>::get(index, tuple, detail::ImplicitConvertGet<T>());
}

// dynamic_get<T>(index, tuple, func) returns func(std::get<index>(tuple)) if func can be called
// with a parameter of type std::tuple_element_t<index>(tuple) or throws a std::invalid_argument
// otherwise. std::out_of_range is thrown when the index is out of bounds of the tuple.
template<class T, class Func, class Tuple>
T dynamic_get(std::size_t index, const Tuple& tuple, const Func& func) {
    return detail::DynamicGetHelper<T, Tuple>::get(index, tuple, func);
}


#include <iostream>

struct Printer {
    template<class T>
    decltype(std::cout << std::declval<T>(), void()) // disable if not printable
    operator()(const T& arg) { std::cout << arg << "\n"; }
};

struct NotPrintable {};

int main(int argc, char** argv) {
    auto x = std::make_tuple(2, "test", 3, 8.4, NotPrintable());

    std::cout << dynamic_get<int>(2, x) << "\n";         // 3
    std::cout << dynamic_get<std::string>(1, x) << "\n"; // test

    // can't implicitly convert from 2 to string
    try { std::cout << dynamic_get<std::string>(0, x) << "\n"; }
    catch (const std::exception& e) { std::cout << e.what() << "\n"; }

    dynamic_get<void>(3, x, Printer());
    
    // can't print NotPrintable(), call operator disabled
    try { dynamic_get<void>(4, x, Printer()); }
    catch (const std::exception& e) { std::cout << e.what() << "\n"; }

    // out of bounds
    try { dynamic_get<void>(5, x, Printer()); }
    catch (const std::exception& e) { std::cout << e.what() << "\n"; }

    return 0;
}