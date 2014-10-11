#include<functional>
#include<iostream>
struct id {};
template <typename T> void each(std::function<void(T)> ){ std::cout << __PRETTY_FUNCTION__ << std::endl; }
template <typename T> void each(std::function<void(T, id)> ){ std::cout << __PRETTY_FUNCTION__ << std::endl; }
template <typename T> void each(std::function<void(T&)> ){ std::cout << __PRETTY_FUNCTION__ << std::endl; }
template <typename T> void each(std::function<void(T&, id)> ){ std::cout << __PRETTY_FUNCTION__ << std::endl; }

template<class T>
struct mem_fn_type;
template<class R, class C, class... T>
struct mem_fn_type<R(C::*)(T...)> {
    using type = std::function<R(T...)>;
};
template<class R, class C, class... T>
struct mem_fn_type<R(C::*)(T...) const> {
    using type = std::function<R(T...)>;
};

// optional extra cv-qualifier and ref-qualifier combos omitted
// since they will never be used with lambdas    

// Detects if a class is a specialization of std::function
template<class T>
struct is_std_function_specialization : std::false_type {};

template<class T>
struct is_std_function_specialization<std::function<T>> : std::true_type{};

// Constrained to not accept cases where T is a specialization of std::function,
// to prevent infinite recursion when a lambda with the wrong signature is passed
template<class T>
typename std::enable_if<!is_std_function_specialization<T>::value>::type each(T func) {
    typename mem_fn_type<decltype(&T::operator())>::type f = func;
    each(f);
}

int main() {
    each([](int){});
    each([](long, id){});
    each([](double&){});
    each([](float&, id){});
}