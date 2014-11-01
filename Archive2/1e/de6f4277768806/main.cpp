#include <cstddef>
#include <functional>
#include <type_traits>
#include <tuple>
#include <utility>

template<typename Functor>
auto curry(Functor&& f);

namespace curry_impl
{
    /* helper: typing using type = T; is tedious */
    template<typename T> struct identity { using type = T; };

    /* helper: SFINAE magic :) */
    template<typename...> struct void_t_impl : identity<void> {};
    template<typename... Ts> using void_t = typename void_t_impl<Ts...>::type;

    /* helper: true iff F(Args...) is invokable */
    template<typename Signature, typename = void> struct is_invokable                                                                    : std::false_type {};
    template<typename F, typename... Args> struct is_invokable<F(Args...), void_t<decltype(std::declval<F>()(std::declval<Args>()...))>> : std::true_type  {};

    /* helper: unwraps references wrapped by std::ref() */
    template<typename T> struct unwrap_reference                            : identity<T>  {};
    template<typename T> struct unwrap_reference<std::reference_wrapper<T>> : identity<T&> {};
    template<typename T> using unwrap_reference_t = typename unwrap_reference<T>::type;

    /* helper: same transformation as applied by std::make_tuple() *
    *         decays to value type unless wrapped with std::ref() *
    *    use: modeling value & reference captures                 *
    *         e.g. c(a) vs c(std::ref(a))                         */
    template<typename T> struct decay_reference : unwrap_reference<std::decay_t<T>> {};
    template<typename T> using decay_reference_t = typename decay_reference<T>::type;

    /* helper: true iff all template arguments are true */
    template<bool...> struct all : std::true_type {};
    template<bool... Booleans> struct all<false, Booleans...> : std::false_type {};
    template<bool... Booleans> struct all<true, Booleans...> : all<Booleans...> {};

    /* helper: std::move(u) iff T is not an lvalue                       *
    *    use: save on copies when curry_t is an rvalue                  *
    *         e.g. c(a)(b)(c) should only copy functor, a, b, etc. once */
    template<bool = false> struct move_if_value_impl       { template<typename U> auto&& operator()(U&& u) { return std::move(u); } };
    template<>             struct move_if_value_impl<true> { template<typename U> auto&  operator()(U&  u) { return u; } };
    template<typename T, typename U> auto&& move_if_value(U&& u) { return move_if_value_impl<std::is_lvalue_reference<T>{}>{}(std::forward<U>(u)); }

    /* the curry wrapper/functor */
    template<typename Functor, typename... Captures>
    struct curry_t {
        /* unfortunately, ref qualifiers don't change *this (always lvalue),   *
        * so qualifiers have to be on operator(),                             *
        * even though only invoke_impl(std::false_type, ...) needs qualifiers */
    #define OPERATOR_PARENTHESES(X, Y) \
        template<typename... Args> \
        auto operator()(Args&&... args) X { \
            return invoke_impl_##Y(is_invokable<Functor(Captures..., Args...)>{}, std::index_sequence_for<Captures...>{}, std::forward<Args>(args)...); \
        }

        OPERATOR_PARENTHESES(&,  lv)
        OPERATOR_PARENTHESES(&&, rv)
    #undef OPERATOR_PARENTHESES

        Functor functor;
        std::tuple<Captures...> captures;

    private:
        /* tag dispatch for when Functor(Captures..., Args...) is an invokable expression *
        * see above comment about duplicate code                             */
    #define INVOKE_IMPL_TRUE(X) \
        template<typename... Args, std::size_t... Is> \
        auto invoke_impl_##X(std::true_type, std::index_sequence<Is...>, Args&&... args) { \
            return functor(std::get<Is>(captures)..., std::forward<Args>(args)...); \
        }

        INVOKE_IMPL_TRUE(lv)
        INVOKE_IMPL_TRUE(rv)
    #undef INVOKE_IMPL_TRUE

        /* tag dispatch for when Functor(Capture..., Args...) is NOT an invokable expression *
        * lvalue ref qualifier version copies all captured values/references     */
        template<typename... Args, std::size_t... Is>
        auto invoke_impl_lv(std::false_type, std::index_sequence<Is...>, Args&&... args) {
            static_assert(all<std::is_copy_constructible<Functor>{}, std::is_copy_constructible<Captures>{}...>{}, "all captures must be copyable or curry_t must an rvalue");
            return curry_t<Functor, Captures..., decay_reference_t<Args>...>{
                functor,
                std::tuple<Captures..., decay_reference_t<Args>...>{
                    std::get<Is>(captures)...,
                    std::forward<Args>(args)...
                }
            };
        }

        /* tag dispatch for when F(As..., Args...) is NOT an invokable expression        *
        * rvalue ref qualifier version moves all captured values, copies all references */
        template<typename... Args, std::size_t... Is>
        auto invoke_impl_rv(std::false_type, std::index_sequence<Is...>, Args&&... args) {
            return curry_t<Functor, Captures..., decay_reference_t<Args>...>{
                move_if_value<Functor>(functor),
                std::tuple<Captures..., decay_reference_t<Args>...>{
                    move_if_value<Captures>(std::get<Is>(captures))...,
                    std::forward<Args>(args)...
                }
            };
        }
    };
}

/* helper function for creating curried functors */
template<typename Functor>
auto curry(Functor&& f) {
    return curry_impl::curry_t<curry_impl::decay_reference_t<Functor>>{std::forward<Functor>(f), {}};
}



#include <iostream>

/* count constructor calls, for the lazy :) */
struct loud {
    static int cnt;
    int id;
    loud()            : id{cnt++} { std::cout << "default " << id << '\n'; }
    loud(const loud&) : id{cnt++} { std::cout << "copy "    << id << '\n'; }
    loud(loud&&)      : id{cnt++} { std::cout << "move "    << id << '\n'; }
    ~loud()                       { std::cout << "dead "    << id << '\n'; }
};
int loud::cnt = 0;

int main() {
    auto a = [](auto&, auto&, auto&, auto&) {};
    curry(a)(loud{}, loud{})(loud{})(loud{});
    
    std::cout << "\n\n";
    
    auto b = curry(a)(loud{});
    b(loud{}, loud{}, loud{});
}