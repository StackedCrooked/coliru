#include <iostream>

template<typename CharT, CharT... X>
struct Str {};

template<typename CharT, CharT... X>
constexpr Str<CharT, X...> operator "" _s ()
{ 
    return {};
}

template<typename CharT, CharT... X, CharT... Y>
constexpr Str<CharT, X..., Y...> concat(Str<CharT, X...>, Str<CharT, Y...>)
{
    return {};
}

template<typename CharT, CharT... X>
constexpr std::basic_string<CharT> make_string(Str<CharT, X...>)
{
    CharT chars[] = {X..., 0};
    return {chars};
}

int main()
{
    auto x = make_string(concat("Hello "_s, "World!"_s));
    std::cout << x << std::endl;
}
