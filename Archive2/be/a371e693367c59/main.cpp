#include <type_traits>

#define STR_1(S,I) (I < sizeof(S) ? S[I] : '\0')
#define STR_2(S,I) STR_1(S,I), STR_1(S,I+1)
#define STR_4(S,I) STR_2(S,I), STR_2(S,I+2)
#define STR_8(S,I) STR_4(S,I), STR_4(S,I+4)
#define STR_16(S,I) STR_8(S,I), STR_8(S,I+8)
#define STR_32(S,I) STR_16(S,I), STR_16(S,I+16)
#define STR_50(S,I) STR_32(S,I), STR_16(S,I+32), STR_2(S,I+48)
#define STR(S) STR_50(S,0)

template <std::size_t... I> 
struct integer_sequence { };

template <std::size_t N, std::size_t... I>
struct make_indices : public make_indices<N - 1, N - 1, I...> { };

template <std::size_t... I>
struct make_indices<0, I...> : public integer_sequence<I...> { 
    typedef integer_sequence<I...> type;
};

template <typename... Tn>
struct types : make_indices<sizeof...( Tn )> {};

template <typename V, V... Vn>
struct values : make_indices<sizeof...( Vn )> {};

namespace tmp_detail {
	template <std::ptrdiff_t i, typename Target, typename T, typename... Tn>
    struct index_of_impl {
		static const std::ptrdiff_t value = index_of_impl<i, Target, T>::value != -1 ? i : index_of_impl<i + 1, Target, Tn...>::value;
	};

	template <std::ptrdiff_t i, typename T>
	struct index_of_impl<i, T, T> {
		static const std::ptrdiff_t value = i;
	};

	template <std::ptrdiff_t i, typename Target, typename T>
	struct index_of_impl <i, Target, T> {
		static const std::ptrdiff_t value = -1;
	};
    
    template <std::ptrdiff_t i, typename V, V Target, V v, V... Vn>
    struct v_index_of_impl {
		static const std::ptrdiff_t value = v_index_of_impl<i, V, Target, v>::value != -1 ? i : v_index_of_impl<i + 1, V, Target, Vn...>::value;
	};

	template <std::ptrdiff_t i, typename V, V Target, V v>
	struct v_index_of_impl<i, V, Target, v> {
		static const std::ptrdiff_t value = Target == v ? i : -1;
	};

    template <std::size_t n, typename T, typename... Tn>
	struct at_impl {
		typedef typename at_impl<n - 1, Tn...>::type type;
	};

	template <typename T, typename... Tn>
	struct at_impl <0, T, Tn...> {
		typedef T type;
	};

    template <std::size_t n, typename V, V v, V... Vn>
	struct v_at_impl {
		static const V value = v_at_impl<n - 1, V, Vn...>::value;
	};

	template <typename V, V v, V... Vn>
	struct v_at_impl <0, V, v, Vn...> {
		static const V value = v;
	};
}

template<std::size_t I, typename... Tn>
struct expanding_at {
    static const std::size_t value = I;
    typedef typename tmp_detail::at_impl<I, Tn...>::type type;
};

template<std::size_t I, typename... Tn>
struct expanding_at<I, types<Tn...>> {
    static const std::size_t value = I;
    typedef typename tmp_detail::at_impl<I, Tn...>::type type;
};

template <typename V, V v, typename List>
struct expanding_v_index_of {
    
};

template <typename V, V v, V... Vn>
struct expanding_v_index_of<V, v, values<V, Vn...>> {
    static const std::ptrdiff_t value = tmp_detail::v_index_of_impl<0, V, v, Vn...>::value;
};

template <typename Tr, typename Tl>
using c_string_equals = std::integral_constant<bool, std::is_same<Tr, Tl>::value>;

template <char... C>
struct c_string {};

template <typename V, typename Ts, typename Tv>
struct const_map {
    template <V v>
    using at = typename expanding_at<expanding_v_index_of<V, v, Tv>::value, Ts>::type;
};

enum class Enum {
    Fucks,
    Shits,
    Stacks,
    Yo
};

int main(){
    typedef types<
            c_string<STR("Park")>,
            c_string<STR("Bae")>,
            c_string<STR("Young")>,
            c_string<STR("Troll")>
        > type_list;
    typedef values<
            Enum,
            Enum::Fucks,
            Enum::Shits,
            Enum::Stacks,
            Enum::Yo
        > value_list;
    typedef const_map<Enum, type_list, value_list> enum_map;
    
    // Lol...
    static_assert( c_string_equals<c_string<STR("hi")>, c_string<STR("hi")>>::value, "Buahahahaa" );
    
    // LEL
    static_assert( c_string_equals<enum_map::at<Enum::Stacks>, c_string<STR("Young")>>::value, "Pfffhuahaha" );
    
}