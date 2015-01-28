#include <cstdio>
#include <memory>
#include <cxxabi.h>

template<char... Cs>
struct Str { using type = Str; };

template <class S, char C>
struct Prepend;

template<char... Cs, char C>
struct Prepend<Str<Cs...>, C> : Str<C, Cs...> {};

template <class S>
struct RemoveEof : S {};

template <char... Cs>
struct RemoveEof<Str<EOF, Cs...>> : Str<> {};

template <char C, char... Cs>
struct RemoveEof<Str<C, Cs...>> : Prepend<typename RemoveEof<Str<Cs...>>::type, C> {};

template <std::size_t N>
constexpr int at(const char (&s)[N], std::size_t i)
{
    return i >= N ? EOF : s[i];
}

#define MAKE_STR(s) \
	RemoveEof<Str<at(s, 0), at(s, 1), at(s, 2), at(s, 3)>>::type

int main()
{
    using s = MAKE_STR("abc");
	
	s abc;
	std::unique_ptr<char[], void (*)(void*)> name(
        abi::__cxa_demangle(typeid(decltype(abc)).name(), nullptr, nullptr, nullptr), std::free);

	std::printf("%s\n", name.get());	
}
