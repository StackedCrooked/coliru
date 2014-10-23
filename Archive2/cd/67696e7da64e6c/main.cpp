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

// now for something a bit more interesting

///   apply :: (a -> b) -> a -> b
///   apply f x = f x
///   apply2 :: (a -> b) -> (b -> c) -> a -> c
///   apply f g x = f (g x)
///   comp :: (a -> b) -> (b -> c) -> (a -> c)
///   comp f g = f . g -- not very helpful to me right now!

template <template <typename...> class f, typename a>
struct apply {
    using type = typename f<a>::type;
};

///   data List a = Nil | Cons a (List a)

//struct Nil;
//template <typename a, typename b,
//    typename = std::enable_if_t<std::is_same<, >> >
//struct Cons {
    

int main()
{
    std::cout << std::boolalpha << std::is_same<apply<f, Nothing>::type, Nothing>::value << std::endl;
    std::cout << typeid(Nothing).name() << std::endl;
    std::cout << typeid(apply<g, Nothing>::type).name() << std::endl;
}
