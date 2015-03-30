#include <experimental/string_view>

constexpr std::experimental::string_view operator""_sv(const char* s, std::size_t n)
{ return { s, n - 1 }; }

template<typename CharT, CharT... Cs> struct string {
    static constexpr CharT data[sizeof...(Cs)+1] = { Cs..., {} };
};

template<typename CharT, CharT... Cs>
constexpr string<CharT, Cs...> operator""_symbol() { return {}; }

constexpr auto make_symbol()
-> decltype( "lol"_symbol )
{ return "lol"_symbol; }

int main()
{
    constexpr auto s = make_symbol();
    static_assert( s.data == "lol"_sv, "" );
}