#include <iostream>

#define STR_1(S,I) (I < sizeof(S) ? S[I] : '\0')
#define STR_2(S,I) STR_1(S,I), STR_1(S,I+1)
#define STR_4(S,I) STR_2(S,I), STR_2(S,I+2)
#define STR_8(S,I) STR_4(S,I), STR_4(S,I+4)
#define STR_16(S,I) STR_8(S,I), STR_8(S,I+8)
#define STR_32(S,I) STR_16(S,I), STR_16(S,I+16)
#define STR_50(S,I) STR_32(S,I), STR_16(S,I+32), STR_2(S,I+48)
#define STR(S) STR_50(S,0)

template <char... C>
struct CParserVarNamed
{
    static_assert(sizeof...(C) == 50, "!");
};

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{
    CParserVarNamed<STR("test")> a;
    TD<decltype(a)>();
}
