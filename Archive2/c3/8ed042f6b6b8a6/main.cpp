#include <cstdlib>
#include <iostream>
#include <type_traits>

template<class Expr, class T = void>
struct enable_if_valid
{
    using type = T;
};

template<class T, class U = void>
using enable_if_valid_t = typename enable_if_valid<T, U>::type;

template<class Sig>
struct sig_of;

template<class R, class C, class... T>
struct sig_of<R(C::*)(T...)>
{
    using type = R(T...);
};

template<class R, class C, class... T>
struct sig_of<R(C::*)(T...) const>
{
    using type = R(T...);
};

template<class Sig>
using sig_of_t = typename sig_of<Sig>::type;

template<class F, class Sig>
struct ref_fn_wrapper
{
    F& f;

    template<class... T>
    decltype(auto) operator()(T&&... t) const
    {
        f(std::forward<T>(t)...);
    }
};

template<class F, class R, class... T>
struct ref_fn_wrapper<F, R(T...)>
{
    F& f;

    R operator()(T... t) const
    {
        f(std::forward<T>(t)...);
    }
};

template<class F, class = void>
struct ref_fn
{
    using type = ref_fn_wrapper<F, void>;
};

template<class F>
struct ref_fn<F, enable_if_valid_t<decltype(&F::operator())>>
{
    using type = ref_fn_wrapper<F, sig_of_t<decltype(&F::operator())>>;
};

template<class F, std::enable_if_t<std::is_function<F>::value, bool> = true>
inline F* tie_fn(F* f)
{
    return f;
}

template<class F>
inline typename ref_fn<F>::type tie_fn(F& f)
{
    return {f};
}

template<class... F>
struct composite
{
    template<class NeverMatch>
    void operator()() const;
};

template<class F, class... Fs>
struct composite<F, Fs...> : F, composite<Fs...>
{
    using F::operator();
    using composite<Fs...>::operator();

    composite(F&& f, Fs&&... fs)
      : F(std::move(f))
      , composite<Fs...>(std::move(fs)...)
    {}
};

template<class F, class... Fs>
struct composite<F*, Fs...> : composite<Fs...>
{
    operator F*() const
    {
        return _f;
    }

    composite(F* f, Fs&&... fs)
      : _f(f)
      , composite<Fs...>(std::move(fs)...)
    {}

    F* _f;
};

template<class... F>
inline composite<F...> make_overload(F... f)
{
    return {std::move(f)...};
}

template<class... F>
inline auto tie_overload(F&&... f)
{
    return make_overload(tie_fn(f)...);
}

struct A{};
struct B{};
struct C{};

template<class F>
void test(F&& f)
{
    A a;
    B b;
    C c;
    int d;
    
    f(a);
    f(b);
    f(c);
    f(d);
}

int main()
{
    using namespace std;
    

    test(tie_overload
    (
        [](A&){ cout << "it's a A!\n"; }
      , [](B&){ cout << "oh, a B!\n"; }
      , [](C&){ cout << "ah yes, a C!\n"; }
      , [](auto&){ cout << "a default!\n"; }
    ));

    return EXIT_SUCCESS;
}
