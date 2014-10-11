#include <type_traits>
#include <initializer_list>
#include <utility>
#include <array>
#include <cstddef>

template<typename T>
struct unqualified {
	typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
};

template <typename T>
using unqualified_t = typename unqualified<T>::type;

template <typename T>
    using type = typename T::type;

	template<typename T>
	struct tmp_void_test { typedef void type; };

	template <typename T>
	using tmp_void_test_t = type<tmp_void_test<T>>;

	template<int i, typename... >
	struct tmp_integer : public std::integral_constant<int, i> {};

	template<bool b, typename... >
	struct tmp_boolean : public std::integral_constant<bool, b> {};

	template<bool b, typename... Tn>
	struct tmp_bool : public tmp_boolean<b, Tn...> {};

	template <bool b, typename... Tn>
	using tmp_bool_t = type<tmp_bool<b, Tn...>>;

	template<typename If, typename Then, typename Else>
	struct tmp_conditional : public std::conditional<If::value, Then, Else> {};

	template <typename If, typename Then, typename Else>
	using tmp_conditional_t = type<tmp_conditional<If, Then, Else>>;

	template<typename T>
	struct tmp_not : public tmp_bool<!T::value> {};

	template <typename T>
	using tmp_not_t = type<tmp_not<T>>;

	template<typename... Tn>
	struct tmp_any : public tmp_bool<true> {};

	template<typename T, typename... Tn>
	struct tmp_any<T, Tn...> : public tmp_conditional_t<T, tmp_bool<true>, type<tmp_any<Tn...>>> {};

	template <typename... Tn>
	using tmp_any_t = type<tmp_any<Tn...>> ;

	template<typename... Tn>
	struct tmp_all : public tmp_bool<true> {};

	template<typename T, typename... Tn>
	struct tmp_all<T, Tn...> : public tmp_conditional_t<T, tmp_all<Tn...>, type<tmp_bool<false>>> {};
	
	template <typename... Tn>
	using tmp_all_t = type<tmp_all<Tn...>>;

	template<typename Lhs, typename Rhs>
	using tmp_or = std::integral_constant<bool, Lhs::value || Rhs::value>;

	template<typename Lhs, typename Rhs>
	using tmp_and = std::integral_constant<bool, Lhs::value && Rhs::value>;

namespace detail {
    
    template <std::ptrdiff_t v1, std::ptrdiff_t... values>
    struct tmp_max {
        static const std::ptrdiff_t value = tmp_max<values...>::value < v1 ? v1 : tmp_max<values...>::value;
    };

    template <std::ptrdiff_t v>
    struct tmp_max<v> {
        static const std::ptrdiff_t value = v;
    };    
}

template <typename T>
struct in_place_of {
    typedef T type;
};

template <typename... Cn>
struct variant {
    std::ptrdiff_t class_idx;
    std::aligned_storage_t<detail::tmp_max<sizeof(Cn)...>::value> storage;
    
    template <typename T, typename... Tn>
    variant ( in_place_of<T>, Tn&&... argn ) {
        new ( &storage )T( std::forward<Tn>(argn)... );
    }
    
    template <typename T>
    variant ( T&& item ) {
        typedef unqualified_t<T> Tu;
        static_assert( tmp_or<typename std::is_same<Cn, Tu>::type...>::value, "Type is not allowed for variant" );
        new ( &storage )Tu( std::forward<T>(item) );
    }
    
};

int main () {

    variant<int, double> f(2.0f);

}