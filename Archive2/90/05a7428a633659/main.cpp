// By Arcoth (c-plusplus.net/forum)

#include <algorithm>
#include <stdexcept>
#include <type_traits>

#include <cstring>

namespace EnumDefaults
{
namespace detail
{
    struct enum_info
	{
		bool increasing;
		bool continuous;
	};

	template <typename T>
	constexpr enum_info information( T const* ptr, std::size_t len, bool increasing = true, bool continuous = true )
	{
		return len == 1? enum_info{increasing, continuous} : information(ptr+1, len-1, increasing && ptr[0] < ptr[1], continuous && ptr[0] + 1 == ptr[1] );
	}
}

	template <char const* const* first, std::size_t len, typename underlying_type, underlying_type const* values>
	std::pair<underlying_type, bool> fromString( char const* str )
	{
		auto i = std::find_if(first, first + len, [str] (char const* arg) {return std::strcmp(arg, str) == 0;});

		if (i == first + len)
			return {values[0], false};

		return {values[i - first], true};
	}
}

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/subseq.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#define STRINGIZE_ENUM(s, data, tuple) BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(0, tuple))

#define EXTRACT_VALUE_1(s, data, tuple) data+1
#define EXTRACT_VALUE_2(s, data, tuple) BOOST_PP_TUPLE_ELEM(1, tuple)
#define EXTRACT_VALUE(s, data, tuple) BOOST_PP_CAT(EXTRACT_VALUE_, BOOST_PP_TUPLE_SIZE(tuple))(s, data, tuple)

#define EXPAND_ENUMERATOR_1(s, data, tuple) BOOST_PP_TUPLE_ELEM(0, tuple)
#define EXPAND_ENUMERATOR_2(s, data, tuple) BOOST_PP_TUPLE_ELEM(0, tuple) = BOOST_PP_TUPLE_ELEM(1, tuple)
#define EXPAND_ENUMERATOR(s, data, tuple) BOOST_PP_CAT(EXPAND_ENUMERATOR_, BOOST_PP_TUPLE_SIZE(tuple))(s, data, tuple)

#define INDEX_MAP(s, N, data) BOOST_PP_SEQ_FOLD_LEFT(EXTRACT_VALUE, BOOST_PP_TUPLE_ELEM(0, data), BOOST_PP_SEQ_SUBSEQ(BOOST_PP_TUPLE_ELEM(1, data), 0, BOOST_PP_INC(N)))

#define TO_STRING_CASE(s, N, data) case BOOST_PP_TUPLE_ELEM(0,BOOST_PP_SEQ_ELEM(N, data)): return strings[N];

#define STRING_ENUM_IMPL(name, namespace_name, seq)                                                                                     \
                                                                                                                                        \
      enum name { BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(EXPAND_ENUMERATOR, 0, seq)) };                                               \
                                                                                                                                        \
      namespace namespace_name                                                                                                          \
      {                                                                                                                                 \
            constexpr std::size_t enum_size = BOOST_PP_SEQ_SIZE(seq);                                                                   \
            using enum_type = decltype(BOOST_PP_TUPLE_ELEM(0,BOOST_PP_SEQ_ELEM(0, seq)));                                               \
            using underlying_type = std::underlying_type<enum_type>::type;                                                              \
                                                                                                                                        \
            constexpr char const* strings[]                                                                                             \
            {                                                                                                                           \
                  BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(STRINGIZE_ENUM, 0, seq))                                                     \
            };                                                                                                                          \
                                                                                                                                        \
            constexpr underlying_type values[]                                                                                          \
            {                                                                                                                           \
                  BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(seq), INDEX_MAP, ((underlying_type) -1, seq))                                         \
            };                                                                                                                          \
                                                                                                                                        \
            constexpr auto info = EnumDefaults::detail::information(values, enum_size);                                                 \
                                                                                                                                        \
            std::pair<enum_type, bool> fromString( char const* str )                                                                    \
            {                                                                                                                           \
                  auto pair = EnumDefaults::fromString<strings, enum_size, underlying_type, values>(str);                               \
                  return {static_cast<enum_type>(pair.first), pair.second};                                                             \
            }                                                                                                                           \
                                                                                                                                        \
            char const* toStringSwitch( enum_type n )                                                                                   \
            {                                                                                                                           \
                  switch (n)                                                                                                            \
                  {                                                                                                                     \
                        BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq), TO_STRING_CASE, seq)                                                    \
                  }                                                                                                                     \
                  return nullptr;                                                                                                       \
            }                                                                                                                           \
                                                                                                                                        \
            char const* toString( enum_type n )                                                                                         \
            {                                                                                                                           \
                  if (info.continuous)                                                                                                  \
                  {                                                                                                                     \
                        if (n - values[0] >= enum_size)                                                                                 \
                              return nullptr;                                                                                           \
                        return strings[n - values[0]];                                                                                  \
                  }                                                                                                                     \
                                                                                                                                        \
                  return toStringSwitch(n);                                                                                             \
            }                                                                                                                           \
      }

#define STRING_ENUM(a, b, ...) STRING_ENUM_IMPL(a, b, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))


STRING_ENUM
(
	MyEnum : unsigned long long, MyEnumInfo,

	(Enumerator1, 7),
	(Enumerator2, 89),
	(Enumerator3)
)

#include <iostream>

int main()
{
	std::cout << MyEnumInfo::toString( MyEnumInfo::fromString("Enumerator1").first ) << '\n';
	std::cout << MyEnumInfo::toString( MyEnumInfo::fromString("Enumerator2").first );
}
