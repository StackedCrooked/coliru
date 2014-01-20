#include <iostream>
#include <type_traits>

namespace std {
    // C++14 utility integer_sequence
	template< typename type__, type__... list__ >
	class integer_sequence {
	public:
		using value_type = type__;
		static std::size_t size( ) { return sizeof...( list__ ); }
	};

    // make_integer_sequence log(n) implementation
	namespace impl {
        // an integer_sequence with a type member
		template<typename type__, type__... list__>
		struct iseq : public integer_sequence<type__, list__...> {
			using type = integer_sequence<type__, list__...>;
		};

        // compress the messy "typename foo<bar>::type
        template<typename type__>
        using inner_type = typename type__::type;
        
        // stich together two iseq
		template<typename a, typename b > struct concat;
		template<typename type__, type__... a__, type__... b__> 
		struct concat<iseq<type__, a__...>, iseq<type__, b__...>> {
            using type = iseq<type__, a__..., (sizeof...(a__) + b__)...>;
		};

        template<typename type__, type__ n__, class = void>
    	struct gen_seq;
        
		template<typename type__, type__ n__>
		struct gen_seq<type__, n__, inner_type< std::enable_if<n__ == 0>>>{
			using type = iseq<type__>;
		};

		template<typename type__, type__ n__>
		struct gen_seq<type__, n__, inner_type< std::enable_if<n__ == 1>>> {
			using type = iseq<type__,0>;
		};

		
		template<typename type__, type__ n__>
		struct gen_seq<type__, n__, inner_type<std::enable_if<(n__ > 1)>>> {
			using type = inner_type<concat< inner_type< gen_seq<type__, n__ / 2>>, inner_type<gen_seq<type__, n__ - n__ / 2>>>>;
		};
	}

    // C++14 utility members related to integer_sequence
	template<typename type__, type__ n__>
	using make_integer_sequence = typename impl::gen_seq<type__, n__>::type;
    
    template<std::size_t n__>
    using make_index_sequence = make_integer_sequence<std::size_t, n__>;
    
    template<std::size_t... list__>
    using index_sequence = integer_sequence<std::size_t, list__...>;
}

template < typename t__, t__... i__>
void display( std::integer_sequence<t__, i__...> ) {
    auto tab = { 0, ( (std::cout << i__ << ", "), 0 )... };(void) tab;
}

int main() {
    display( std::make_index_sequence<12>() );
}
