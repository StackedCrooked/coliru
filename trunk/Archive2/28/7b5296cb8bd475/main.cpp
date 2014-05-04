#include <iostream>
#include <type_traits>

template <char... symbols>
struct String
{
    static constexpr char value[] = {symbols...};
};

template <char... symbols>
constexpr char String<symbols...>::value[];

template <typename, typename>
struct Concat;

template <char... symbols1, char... symbols2>
struct Concat<String<symbols1...>, String<symbols2...>>
{
    using type = String<symbols1..., symbols2...>;
};

template <typename...>
struct Concatenate;

template <typename S, typename... Strings>
struct Concatenate<S, Strings...>
{
    using type = typename Concat<S, typename Concatenate<Strings...>::type>::type;
};

template <>
struct Concatenate<>
{
    using type = String<>;
};

template <std::size_t N>
struct NumberToString
{
    using type = typename Concat
        <
            typename std::conditional<(N >= 10), typename NumberToString<N / 10>::type, String<>>::type,
            String<'0' + N % 10>
        >::type;
};

template <>
struct NumberToString<0>
{
    using type = String<'0'>;
};

constexpr const std::uint8_t major = 1;
constexpr const std::uint8_t minor = 10;
constexpr const std::uint8_t bugfix = 0;

using VersionString = Concatenate
    <
        NumberToString<major>::type,
        String<'.'>,
        NumberToString<minor>::type,
        String<'.'>,
        NumberToString<bugfix>::type
    >::type;

constexpr const char* version_string = VersionString::value;

int main()
{
    std::cout << version_string << std::endl;
}