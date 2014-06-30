#include <type_traits>
#include <vector>
#include <utility>

namespace detail {
template <typename T, typename... Args>
struct callable_with_args_ {
    template <typename U=T>
    static auto test(int) -> decltype((void)std::declval<U>()(std::declval<Args>()...), std::true_type());
    static auto test(...) -> std::false_type;
    using type = decltype(test(0));
};

template <typename T, typename... Args>
using callable_with_args = typename callable_with_args_<T const&, typename std::add_lvalue_reference<Args>::type...>::type;

template <typename T, typename... Args>
struct callable_without_args_ {
    template <typename U=T>
    static auto test(int) -> decltype((void)std::declval<T>()(), std::true_type());
    static auto test(...) -> std::false_type;
    using type = decltype(test(0));
};

template <typename T>
using callable_without_args = typename callable_without_args_<T const&>::type;

template < class T >
void update_callable_no_args(std::false_type, const std::vector<T>&) {}

template < class T >
void update_callable_no_args(std::true_type, const std::vector<T>& objects) {
    for (auto&& i : objects) {
        i();
    }
}

template< class T, class... Args >
void update_callable_args(std::false_type, const std::vector<T>& objects, Args&&... ) {
    update_callable_no_args(callable_without_args<T>(), objects);
}

template< class T, class... Args >
void update_callable_args(std::true_type, const std::vector<T>& objects, Args&&... args ) {
    for (auto&& i : objects) {
        i(args...);
    }
}
} // namespace detail

template< class T, class... Args >
void update_callable( const std::vector<T>& objects, Args&&... args ) {
    detail::update_callable_args(detail::callable_with_args<T, Args...>(),
                                 objects, std::forward<Args>(args)...);
}

#include <iostream>

template <typename... Args>
struct Callable {
    void operator () (Args... args) const {
        std::cout << "Callable(" << this << "): ";
        (void)std::initializer_list<int>{0, ((void)(std::cout << args << ' '), 0)...};
        std::cout << '\n';
    }
};

int main() {
    update_callable(std::vector<Callable<int, double>>(4), 1, 3.14159);
    update_callable(std::vector<Callable<>>(4), 1, 3.14159);
}
