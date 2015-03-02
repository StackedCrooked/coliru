#include <iostream>

template <char... Chars>
struct MyStruct
{
    static constexpr char value[] {Chars..., '\0'};
};

template <char... Chars>
constexpr char MyStruct<Chars...>::value[];

template <typename, typename>
struct Together;

template <char... Chars1, char... Chars2>
struct Together<MyStruct<Chars1...>, MyStruct<Chars2...>>
{
    using type = MyStruct<Chars1..., Chars2...>;
};

int main()
{
    std::cout << Together<MyStruct<'a', 'b'>, MyStruct<'c', 'd'>>::type::value << std::endl;
}