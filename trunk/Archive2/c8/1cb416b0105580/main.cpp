#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <tuple>

    template<typename T>
    struct unqualified {
		typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type type;
	};

	template <typename T>
	using unqualified_t = typename unqualified<T>::type;

    template<class T>
    struct void_type {
		typedef void type;
	};

	template <typename T>
	using void_type_t = typename void_type<T>::type;
    
    template<class T>
    struct is_c_array : std::false_type { };

	template<class T>
	struct is_c_array<T []> : std::true_type{ };

	template<class T, std::size_t n>
	struct is_c_array<T[ n ]> : std::true_type{ };

    namespace detail {
        // TODO: We'll do better once the port to g++ is done
    	template<class T, class U = void>
    	struct has_iterator {
    		static const bool value = false;
    	};
    
    	template<class T>
    	struct has_iterator<T, typename void_type<typename T::iterator>::type> {
    		static const bool value = true;
    	};
    }
    
    template <typename T>
    struct is_rangeable : public std::integral_constant<bool, detail::has_iterator<T>::value || is_c_array<T>::value> {
    
    };
    
    template <typename T>
    using tmp_type = typename T::type;

	template<int i, typename... >
	struct tmp_integer : public std::integral_constant<int, i> {};

	template<bool b, typename... >
	struct tmp_boolean : public std::integral_constant<bool, b> {};

	template<bool b, typename... Tn>
	struct tmp_bool : public tmp_boolean<b, Tn...> {};

	template <bool b, typename... Tn>
	using tmp_bool_t = tmp_type<tmp_bool<b, Tn...>>;

	template<typename If, typename Then, typename Else>
	struct tmp_conditional : public std::conditional<If::value, Then, Else> {};

	template <typename If, typename Then, typename Else>
	using tmp_conditional_t = tmp_type<tmp_conditional<If, Then, Else>>;

	template<typename T>
	struct tmp_not : public tmp_bool<!T::value> {};

	template <typename T>
	using tmp_not_t = tmp_type<tmp_not<T>>;

	template<typename... Tn>
	struct tmp_any : public tmp_bool<true> {};

	template<typename T, typename... Tn>
	struct tmp_any<T, Tn...> : public tmp_conditional_t<T, tmp_bool<true>, tmp_type<tmp_any<Tn...>>> {};

	template <typename... Tn>
	using tmp_any_t = tmp_type<tmp_any<Tn...>> ;

	template<typename... Tn>
	struct tmp_all : public tmp_bool<true> {};

	template<typename T, typename... Tn>
	struct tmp_all<T, Tn...> : public tmp_conditional_t<T, tmp_all<Tn...>, tmp_type<tmp_bool<false>>> {};
	
	template <typename... Tn>
	using tmp_all_t = tmp_type<tmp_all<Tn...>>;

namespace Encoding {
    
    typedef char charascii;
    typedef unsigned char charutf8;
    typedef uint16_t charutf16;
    typedef uint32_t charutf32;
    typedef wchar_t charwide;
    typedef charwide charfs;
    typedef uint32_t codepoint;
    
    struct ascii { typedef charascii code_unit; };
    struct utf8 { typedef charutf8 code_unit; };
    struct utf16le { typedef charutf16 code_unit; };
    struct utf16be { typedef charutf16 code_unit; };
    struct utf32le { typedef charutf32 code_unit; };
    struct utf32be { typedef charutf32 code_unit; };
    
    typedef utf32le wide_encoding;
    typedef utf16le utf16;
    typedef utf32le utf32;
    
    template <typename TSrc, typename TDest>
	struct compatible_encoding : std::is_same<TSrc, TDest> {
		
	};

	template <>
	struct compatible_encoding<ascii, utf8> : std::true_type {
		
	};

	template <typename TChar>
	struct default_encoding {
		static const bool value = false;
		typedef void type;
	};

	template <>
	struct default_encoding<char> {
		static const bool value = true;
		typedef utf8 type;
	};

	template <>
	struct default_encoding<signed char> {
		static const bool value = true;
		typedef utf8 type;
	};

	template <>
	struct default_encoding<charutf8> {
		static const bool value = true;
		typedef utf8 type;
	};

	template <>
	struct default_encoding<charutf16> {
		static const bool value = true;
		typedef utf16 type;
	};

	template <>
	struct default_encoding<charutf32> {
		static const bool value = true;
		typedef utf32 type;
	};

	template <>
	struct default_encoding<charwide> {
		static const bool value = true;
		typedef wide_encoding type;
	};
}

template <typename TEnco>
struct action_roll {
private:
    typedef TEnco encoding_type;
    typedef typename TEnco::code_unit code_unit;

    const static std::size_t direct = 0;
    const static std::size_t compat = 1;
    const static std::size_t none = 2;

    template <typename TRange, typename TAction>
    void do_ranged( std::true_type, TRange&& range, TAction&& action ) {
    	using std::begin;
    	typedef unqualified_t<decltype( *begin( range ) )> other_code_unit;
    	typedef typename Encoding::default_encoding<other_code_unit>::type TEnco0;
    	typedef typename tmp_all_t<std::is_same<unqualified_t<TEnco0>, encoding_type>, std::is_same<code_unit, other_code_unit>>::type is_direct_match;
    	do_direct( is_direct_match(), std::forward<TRange>( range ), TEnco0( ), std::forward<TAction>( action ) );
    }
    
    template <typename TRange, typename TAction>
    void do_ranged( std::false_type, TRange&& value, TAction&& action ) {
    	typedef unqualified_t<TRange> value_type;
        typedef value_type other_code_unit;
    	value_type range[ 1 ] = { value_type( std::forward<TRange>( value ) ) };
    	typedef typename Encoding::default_encoding<other_code_unit>::type TEnco0;
    	typedef typename tmp_all_t<std::is_same<unqualified_t<TEnco0>, encoding_type>, std::is_same<code_unit, other_code_unit>>::type is_direct_match;
    	do_direct( is_direct_match( ), range, TEnco0( ), std::forward<TAction>( action ) );
    }
    
    template <typename TRange, typename TEnco0, typename TAction>
    void do_ranged( std::true_type, TRange&& range, TEnco0&& enc, TAction&& action ) {
    	typedef typename TEnco0::code_unit other_code_unit;
    	typedef typename tmp_all_t<std::is_same<unqualified_t<TEnco0>, encoding_type>, std::is_same<code_unit, other_code_unit>>::type is_direct_match;
    	do_direct( is_direct_match(), std::forward<TRange>( range ), std::forward<TEnco0>( enc ), std::forward<TAction>( action ) );
    }
    
    template <typename TRange, typename TEnco0, typename TAction>
    void do_ranged( std::false_type, TRange&& value, TEnco0&& enc, TAction&& action ) {
    	typedef typename TEnco0::code_unit other_code_unit;
    	typedef typename tmp_all_t<std::is_same<unqualified_t<TEnco0>, encoding_type>, std::is_same<code_unit, other_code_unit>>::type is_direct_match;
    	unqualified_t<TRange> range[ 1 ] = { value };
    	do_direct( is_direct_match(), range, std::forward<TEnco0>( enc ), std::forward<TAction>( action ) );
    }
    
    template <typename TRange, typename TEnco0, typename TAction>
    void do_direct( std::true_type, TRange&& value, TEnco0&& enc, TAction&& action ) {
    	std::get<direct>( action )( std::forward<TRange>( value ), std::forward<TEnco0>( enc ), std::forward<TAction>( action ) );
    }
    
    template <typename TRange, typename TEnco0, typename TAction>
    void do_direct( std::false_type, TRange&& value, TEnco0&& enc, TAction&& action ) {
    	typedef typename Encoding::compatible_encoding<unqualified_t<TEnco0>, encoding_type> is_compatible;
    	do_compat( is_compatible( ), std::forward<TRange>( value ), std::forward<TEnco0>( enc ), std::forward<TAction>( action ) );
    }
    
    template <typename TRange, typename TEnco0, typename TAction>
    void do_compat( std::true_type, TRange&& value, TEnco0&& enc, TAction&& action ) {
        std::get<compat>( action )( std::forward<TRange>( value ), std::forward<TEnco0>( enc ), std::forward<TAction>( action ) );
    }
    
    template <typename TRange, typename TEnco0, typename TAction>
    void do_compat( std::false_type, TRange&& value, TEnco0&& enc, TAction&& action ) {
        std::get<none>( action )( std::forward<TRange>( value ), std::forward<TEnco0>( enc ), std::forward<TAction>( action ) );
    }
    
public:
    template <typename TRange, typename TEnco0, typename TAction>
	void getdo( TRange&& value, TEnco0&& enc, TAction&& action ) {
		typedef unqualified_t<TRange> Tu;
		typedef is_rangeable<Tu> is_ranged;
		do_ranged( is_ranged( ), std::forward<TRange>( value ), std::forward<TEnco0>( enc ), std::forward<TAction>( action ) );
	}
	
	template <typename TRange, typename TAction>
	void getdo( TRange&& value, TAction&& action ) {
		typedef unqualified_t<TRange> Tu;
		typedef is_rangeable<Tu> is_ranged;
		do_ranged( is_ranged( ), std::forward<TRange>( value ), std::forward<TAction>( action ) );
	}
};

#include <iostream>

struct direct_do {
    template <typename... Tn>
    void operator () ( Tn&&... ) {
        std::cout << "Direct path taken" << std::endl;
    }
};

struct compat_do {
    template <typename... Tn>
    void operator () ( Tn&&... ) {
        std::cout << "Not directly the same, but are compatible" << std::endl;
    }
};

struct none_do {
    template <typename... Tn>
    void operator () ( Tn&&... ) {
        std::cout << "Cannot take direct or compat path..." << std::endl;
    }
};

int main () {
    
    action_roll<Encoding::utf8> roll{};
    auto actions = std::make_tuple(
        direct_do(),
        compat_do(),
        none_do()
    );
    
    auto& woof = "Woof!";
    auto& woof2 = L"Woof!";
    const unsigned char woof3[5] = "Woof";
    
    roll.getdo( woof, actions );
    roll.getdo( woof2, actions );
    roll.getdo( woof3, actions );
    
}