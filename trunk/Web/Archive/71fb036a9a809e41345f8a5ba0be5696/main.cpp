#include <utility>
#include <type_traits>

// SFINAE utility
template<typename...> struct void_ { using type = void; };
template<typename... T> using Void = typename void_<T...>::type;

/*
 * In an ideal world std::result_of would just work instead of all that.
 * Consider this as a write-once (until std::result_of is fixed), use-many
 * situation.
 */    
template<typename Sig, typename Sfinae = void> struct result_of {};
template<typename F, typename... Args>
struct result_of<
    F(Args...)
    , Void<decltype(std::declval<F>()(std::declval<Args>()...))>
> {
    using type = decltype(std::declval<F>()(std::declval<Args>()...));
};
template<typename Sig> using ResultOf = typename result_of<Sig>::type;

/*
 * Note how both template parameters have kind *, MonadicValue would be
 * m a, not m. We don't whether MonadicValue is a specialization of some M<T>
 * or not (or derived from a specialization of some M<T>). Note that it is
 * possible to retrieve the a in M a via typename MonadicValue::value_type
 * if MonadicValue is indeed a model of the proper concept.
 *
 * Defer actual implementation to the operator() of MonadicValue,
 * which will do the monad-specific operation
 */
template<
    typename MonadicValue
    , typename F
    /* It is possible to put a self-documenting assertion here
       that will *not* SFINAE out but truly result in a hard error
       unless some conditions are not satisfied -- I leave this out
       for brevity
    , Requires<
        MonadicValueConcept<MonadicValue>
        // The two following constraints ensure that
        // F has signature a -> m b
        , Callable<F, ValueType<MonadicValue>>
        , MonadicValueConcept<ResultOf<F(ValueType<MonadicValue>)>>
    >...
    */
>
ResultOf<MonadicValue(F)>
bind(MonadicValue&& value, F&& f)
{ return std::forward<MonadicValue>(value)(std::forward<F>(f)); }

// Picking Maybe as an example monad because it's easy
template<typename T>
struct just_type {
    using value_type = T;

    // Encapsulation omitted for brevity
    value_type value;

    template<typename F>
    // The use of ResultOf means that we have a soft contraint
    // here, but the commented Requires clause in bind happens
    // before we would end up here
    ResultOf<F(value_type)>
    operator()(F&& f)
    { return std::forward<F>(f)(value); }
};

template<typename T>
just_type<T> just(T&& t)
{ return { std::forward<T>(t) }; }

template<typename T>
just_type<typename std::decay<T>::type> make_just(T&& t)
{ return { std::forward<T>(t) }; }

struct nothing_type {
    // Note that because nothing_type and just_type<T>
    // are part of the same concept we *must* put in
    // a value_type member type -- whether you need
    // a value member or not however is a design
    // consideration with trade-offs
    struct universal { template<typename T> operator T(); };
    using value_type = universal;

    template<typename F>
    nothing_type operator()(F const&) const
    { return {}; }
};
constexpr nothing_type nothing;
    
#include <cassert>
    
int main()
{
    auto maybe = make_just(4);
    auto f = [](int i) { return just("Hello, World!"[i]); };
    auto&& r0 = bind(maybe, f);
    auto&& r1 = bind(bind(make_just(6), [](int i) { return just(i - 2); }), f);
    assert( &r0.value == &r1.value );
    auto r2 = bind(nothing, f);
    auto r3 = bind(maybe, [](int) { return nothing; });
    static_assert( std::is_same<decltype(r2), nothing_type>::value, "" );
    static_assert( std::is_same<decltype(r3), nothing_type>::value, "" );
}