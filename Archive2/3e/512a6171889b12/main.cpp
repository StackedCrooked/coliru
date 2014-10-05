#include <type_traits>
template <typename T>
struct return_type;

template <typename R, typename... Args>
struct return_type<R (Args...)> { using type = R; };

template <typename R, typename... Args>
struct return_type<R(*)(Args...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...)> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) &> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) &&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) volatile&&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const volatile> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const volatile&> { using type = R; };

template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const volatile&&> { using type = R; };

// leave undefined
template<class C, class T>
T return_type_helper(T (C::*)(T));

template<class C, class T>
T return_type_helper(T (C::*)(T) const);

// 10 other combinations of possible ref- and cv- qualifiers omitted

template<typename T>
using functor_return_type = decltype(return_type_helper(&T::operator()));
    
template <typename... T>
struct voider { using type = void; };
template <typename... T>
using void_t = typename voider<T...>::type;

template<typename T, typename = void>
struct combined_return_type;
template<typename T>
struct combined_return_type<T, void_t<typename return_type<T>::type>> { using type = typename return_type<T>::type;};
template<typename T>
struct combined_return_type<T, void_t<functor_return_type<T>>> { using type = functor_return_type<T>; };
template <typename T>
using return_type_t = typename combined_return_type<T>::type;

int f();

struct test { int operator()(int) const; double operator()(long); };
struct fail { };
int main(){
    return_type_t<decltype(f)> foo;
    return_type_t<test> bar;
    // return_type_t<fail> baz;
    static_assert(std::is_same<decltype(foo), int>::value, "Oops");
    static_assert(std::is_same<decltype(bar), int>::value, "Oops");
}