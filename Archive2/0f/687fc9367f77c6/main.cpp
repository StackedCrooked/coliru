#include <iostream>
#include <utility>
#include <tuple>

template <class T, class...> struct interlace_ {using type = T;};
template <class... res,  template<class...> class templ, class f, class... r, class... packs>
struct interlace_<std::tuple<res...>, templ<f, r...>, packs...>
    : interlace_<std::tuple<res..., f>, packs..., std::tuple<r...>> {};
template <class... res, template<class...> class templ, class f, class... packs>
struct interlace_<std::tuple<res...>, templ<f>, packs...>
    : interlace_<std::tuple<res..., f>, packs...> {};

template <class... packs>
using interlace = interlace_<std::tuple<>, packs...>;

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
    print<interlace<TestPack1, TestPack2, TestPack3>::type>();
}
