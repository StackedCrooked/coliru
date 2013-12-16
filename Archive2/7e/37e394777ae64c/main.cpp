#include <type_traits>
#include <utility>

template <typename T>
struct can_dereference_helper {
    template <typename U, typename = decltype(*std::declval<U>())>
    static std::true_type test(U);
    template <typename...U>
    static std::false_type test(U...);
    using type = decltype(test(std::declval<T>()));
};

template <typename T>
struct can_dereference :
  can_dereference_helper<typename std::decay<T>::type>::type {};

template <typename T>
auto dereference(const T& v, std::false_type) -> decltype(v) {
    return v;
}

template <typename T>
auto dereference(const T& v, std::true_type) -> decltype(*v) {
    return *v;
}

template <typename T>
auto dereference(const T& t) ->
  decltype(dereference(t, can_dereference<T>{})) {
    return dereference(t, can_dereference<T>{});
}

template <typename T>
auto recursive_dereference(T&& t, std::false_type) ->
  decltype(std::forward<T>(t)) {
    return std::forward<T>(t);
}

template <typename T>
auto recursive_dereference(T&& t) ->
  decltype(recursive_dereference(std::forward<T>(t), can_dereference<T>{}));

template <typename T>
auto recursive_dereference(T&& t, std::true_type) ->
  decltype(recursive_dereference(*std::forward<T>(t))) {
    return recursive_dereference(*std::forward<T>(t));
}

template <typename T>
auto recursive_dereference(T&& t) ->
  decltype(recursive_dereference(std::forward<T>(t), can_dereference<T>{})) {
    return recursive_dereference(std::forward<T>(t), can_dereference<T>{});
}

#include <iostream>
#include <memory>

int main() {
    {
        auto x = 42;
        auto p1 = &x;
        auto p2 = &p1;
        std::cout << "dereference(" << p2 << ") = " << dereference(p2) << '\n';
        std::cout << "recursive_dereference(" << p2 << ") = " << recursive_dereference(p2) << '\n';
    }
    {
        std::unique_ptr<int> foo{new int{13}};
        auto p1 = &foo;
        auto p2 = &p1;
        std::cout << "dereference(" << p2 << ") = " << dereference(p2) << '\n';
        std::cout << "recursive_dereference(" << p2 << ") = " << recursive_dereference(p2) << '\n';
    }
}
