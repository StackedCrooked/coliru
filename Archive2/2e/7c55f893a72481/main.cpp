#include <iostream>
#include <utility>
#include <tuple>

template <typename T, typename... packs> struct interlace {using type = T;};
template <typename... res,  template<class...> class templ, typename f, typename... r, typename... packs>
struct interlace<std::tuple<res...>, templ<f, r...>, packs...>
    : interlace<std::tuple<res..., f>, packs..., std::tuple<r...>> {};
template <typename... res, template<class...> class templ, typename f, typename... packs>
struct interlace<std::tuple<res...>, templ<f>, packs...>
    : interlace<std::tuple<res..., f>, packs...> {};

/// TEST:
    
template <typename T> void print () {std::cout << __PRETTY_FUNCTION__;}

template <typename...> struct Pack {};
template <typename...> struct Group {};
template <typename...> struct Wrap {};
struct Object {};  struct Blob {};

using TestPack1 = Pack<int, double, Object>;  // 3 types
using TestPack2 = Group<double, char, int, short, long>;  // 5 types
using TestPack3 = Wrap<char, short, Blob, char>;  // 4 types

int main()
{
    print<interlace<std::tuple<>, TestPack1, TestPack2, TestPack3>::type>();
}
