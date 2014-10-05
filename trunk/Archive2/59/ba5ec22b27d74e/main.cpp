template <typename T>
struct return_type;

template <typename R, typename... Args>
struct return_type<R(Args...)> { using type = R; };

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

template <typename T>
using return_type_t = typename return_type<T>::type;

#include <type_traits>

struct Functor
{
    int operator()(int i, int j) { return i + j; }
};

template <class F>
struct A
{
    using T = return_type_t<decltype(&F::operator())>;
    T some_function(T i) { return (T)1; }
};

int main()
{
    A<Functor> a;
    static_assert(std::is_same<decltype(a.some_function(1)), int>::value, "!");
}
