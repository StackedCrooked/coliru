
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/stringize.hpp>

template <char... ch>
struct const_string {static constexpr char array[] {ch..., '\0'};};
template <char... ch>
constexpr char const_string<ch...>::array[];

template <char c1, char c2, typename, typename=const_string<>>
struct rtrim;

template <char c1, char c2, char f, char... prev, char... next>
struct rtrim<c1, c2, const_string<f, next...>, const_string<prev...>> :
    rtrim<c1, c2, const_string<next...>, const_string<prev..., f>> {};

template <char c1, char c2, char... prev, char... next>
struct rtrim<c1, c2, const_string<c1, next...>, const_string<prev...>> :
	const_string<prev...> {};
template <char c1, char c2, char... prev, char... next>
struct rtrim<c1, c2, const_string<c2, next...>, const_string<prev...>> :
	const_string<prev...> {};
template <char c1, char c2, char... prev>
struct rtrim<c1, c2, const_string<>, const_string<prev...>> :
	const_string<prev...> {};

#define SPLIT_1(s, x) ( x < sizeof(s) ? s[x] : '\n' )
#define SPLIT_4(s, x) SPLIT_1  (s, x), SPLIT_1  (s, x+1)  , SPLIT_1  (s, x+2)  , SPLIT_1  (s, x+3)
#define SPLIT_16(s, x) SPLIT_4  (s, x), SPLIT_4  (s, x+4)  , SPLIT_4  (s, x+8)  , SPLIT_4  (s, x+12)
#define SPLIT_64(s, x) SPLIT_16 (s, x), SPLIT_16 (s, x+16) , SPLIT_16 (s, x+32) , SPLIT_16 (s, x+48)

#define STRINGIZE_ENUM(s, data, elem) (rtrim<'=', '\0', const_string<SPLIT_64(BOOST_PP_STRINGIZE(elem), 0)>>::array)

#define STRING_ENUM(name, string_array_name, ...)   \
                                                    \
	enum name { __VA_ARGS__ };                      \
                                                    \
	constexpr char const* string_array_name[]          \
	{                                                                                                        \
		BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(STRINGIZE_ENUM, 0, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))  \
	};
    
#include <cstddef> // std::size_t

STRING_ENUM(MyEnum : std::size_t, MyEnumStrings,
	Enumerator1 = 7,
	Enumerator2)

#include <iostream>

int main()
{
	for (auto str : MyEnumStrings)
		std::cout << str << '\n';
}
