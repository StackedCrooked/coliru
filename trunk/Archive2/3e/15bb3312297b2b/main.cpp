#include <iostream>

#define STR_1(S,I) (I < sizeof(S) ? S[I] : '\0')
#define STR_2(S,I) STR_1(S,I), STR_1(S,I+1)
#define STR_4(S,I) STR_2(S,I), STR_2(S,I+2)
#define STR_8(S,I) STR_4(S,I), STR_4(S,I+4)
#define STR_16(S,I) STR_8(S,I), STR_8(S,I+8)
#define STR_32(S,I) STR_16(S,I), STR_16(S,I+16)
#define STR(S) STR_32(S,0)

template <char... Chars>
struct MyString
{
    static constexpr char value[] = { Chars..., '\0' };
};

template <char... Chars>
constexpr char MyString<Chars...>::value[];

template <const char* Str>
void print()
{
    std::cout << Str << std::endl;
}

int main()
{
    print<MyString<STR("Hello")>::value>();
}
