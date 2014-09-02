#include <iostream>
#include <typeinfo>
#include <functional>

template<typename T> struct remove_class { };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...)> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) volatile> { using type = R(A...); };
template<typename C, typename R, typename... A>
struct remove_class<R(C::*)(A...) const volatile> { using type = R(A...); };

template<typename T>
struct get_signature_impl { using type = typename remove_class<
    decltype(&std::remove_reference<T>::type::operator())>::type; };
template<typename R, typename... A>
struct get_signature_impl<R(A...)> { using type = R(A...); };
template<typename R, typename... A>
struct get_signature_impl<R(&)(A...)> { using type = R(A...); };
template<typename R, typename... A>
struct get_signature_impl<R(*)(A...)> { using type = R(A...); };
template<typename T> using get_signature = typename get_signature_impl<T>::type;

template<typename F> using make_function_type = std::function<get_signature<F>>;

namespace detail {

template <typename Function, typename Sig>
struct check_function
{
    static constexpr bool value =
        std::is_convertible<Function, typename std::decay<Sig>::type>::value;
};

template <typename, typename>
struct check_functor;

template <typename Functor, typename Ret, typename... Args>
struct check_functor<Functor, Ret(Args...)>
{
    typedef Ret (Functor::*Memfn) (Args...);

    static constexpr bool value =
        check_function<decltype(&Functor::operator()), Memfn>::value;
};

} // end namespace detail

template <typename Func, typename Sig>
struct check_function_signature
{
    using Type =
        typename std::conditional<
                     std::is_function<Func>::value,
                     detail::check_function<Func, Sig>,
                     detail::check_functor<Func, Sig>>::type;

    static const bool value = Type::value;
};

int f(int i);

struct g
{
    int operator() (int i) { return i; }
};

int main(){
    auto l = [](int i){ return i; };
    static_assert(check_function_signature<get_signature<decltype(l)>, int(int)>::value,
                  "Fails");
}