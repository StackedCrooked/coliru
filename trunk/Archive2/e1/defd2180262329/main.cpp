#include <iostream>
#include <string>
#include <vector>

template<std::size_t N>
struct string_literal
{
    char data[N];
};

constexpr auto process2(char c)
    -> char
{
    return (c >= '0' && c <= '9') ? c - '0' :
        (c >= 'a' && c <= 'f') ? c - 87 :
            (c >= 'A' && c <= 'F') ? c - 55 :
                throw;
}

template<char, char, char... Chars>
constexpr auto process()
    -> string_literal<sizeof...(Chars)>
{
    return { process2(Chars)... };
}

template<char... Chars>
auto operator "" _hex()
    -> string_literal<sizeof...(Chars)-2>
{
    return process<Chars...>();

}

int main()
{
    auto str = 0x34a353F6_hex;
    for (auto c: str.data)
    {
        std::cout << int(c) << ' ';
    }
}
