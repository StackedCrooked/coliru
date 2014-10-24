#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <typeinfo>

///   data Maybe a = Nothing | Some a

// these aren't metafunctions, they're just 'tags' (sort of).
struct Nothing {};
template <typename a>
struct Some {};

// type-trait (sort of optional type checking)
template <typename...>
struct Maybe {
    static constexpr bool value = false;
};

template <>
struct Maybe<Nothing> {
    static constexpr bool value = true;
};

template <typename a>
struct Maybe<Some<a>> {
    static constexpr bool value = true;
};

///   f :: a -> Maybe a -- again dubious, but who cares?
///   f x = Some x
///   g :: Maybe a -> Maybe a -- basically id specialised for Maybe
///   g (Some x) = Some x
///   g Nothing = Nothing

template <typename x>
struct f {
    using type = Some<x>;
};

template <typename...>
struct g;

template <typename x>
struct g<Some<x>> {
    using type = Some<x>;
};

template <>
struct g<Nothing> {
    using type = Nothing;
};

///   data Natural = Zero | Succ Natural
///   plusOne :: Natural -> Natural
///   plusOne Zero = Succ Zero
///   plusOne (Succ x) = Succ (Succ x)

struct Zero {
    static constexpr int value = 0;
};
template <typename x>
struct Succ {
    static constexpr int value = 1 + x::value;
};

template <typename...>
struct Natural {
    static constexpr bool value = false;
};

template <>
struct Natural<Zero> {
    static constexpr bool value = true;
};

template <typename x>
struct Natural<Succ<x>> {
    static constexpr bool value = true;
};

template <typename...>
struct plusOne;

template <>
struct plusOne<Zero> {
    using type = Succ<Zero>;
};

template <typename x>
struct plusOne<Succ<x>> {
    using type = Succ<Succ<x>>;
};

// now for something a bit more interesting

///   apply :: (a -> b) -> a -> b
///   apply f x = f x
///   apply2 :: (a -> b) -> (b -> c) -> a -> c
///   apply f g x = f (g x)
///   comp :: (a -> b) -> (b -> c) -> (a -> c)
///   comp f g = f . g -- not very helpful to me right now!

template <template <typename...> class f, typename x>
struct apply {
    using type = typename f<x>::type;
};

template <template <typename...> class f, template <typename...> class g, typename x>
struct apply2 {
    using type = typename f<typename g<x>::type>::type;
};

template <template <typename...> class f, template <typename...> class g>
struct comp {
    template <typename... args>
    struct type_ {
        using type = typename f<typename g<args...>::type>::type;
    };
    
    template <typename... args>
    using type = type_<args...>;
};

///   data List a = Nil | Cons a (List a)

//struct Nil;
//template <typename a, typename b,
//    typename = std::enable_if_t<std::is_same<, >> >
//struct Cons {


int main()
{
    using namespace std;
    cout << boolalpha << std::is_same<apply<g, Nothing>::type, Nothing>::value << std::endl;
    //cout << comp<plusOne, plusOne>::type<Zero>::value << std::endl;
    
    cout << apply<comp<plusOne, plusOne>::type, Zero>::type::value << std::endl;
}
