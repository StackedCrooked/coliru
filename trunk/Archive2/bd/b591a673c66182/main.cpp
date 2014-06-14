#include <iostream>
#include <tuple>
#include <string>
#include <utility>
#include <type_traits>

template <int FIRST, int... REST>
struct select_tuple {
    template <typename TUPLE>
	auto operator() (const TUPLE& t) const -> decltype (std::tuple_cat (std::make_tuple (std::get<FIRST>(t)), select_tuple<REST...>()(t))) {
		return std::tuple_cat (std::make_tuple (std::get<FIRST>(t)), select_tuple<REST...>()(t));
	}

	template< typename TUPLE > struct result_type {
	    using type = decltype( select_tuple<FIRST,REST...>()( std::declval<TUPLE>() ) ) ; };
};

template <int LAST>
struct select_tuple <LAST> {
	template <typename TUPLE>
	auto operator() (const TUPLE& t) const -> decltype (std::make_tuple (std::get<LAST>(t))) {
		return std::make_tuple (std::get<LAST>(t));
	}

	template< typename TUPLE > struct result_type {
	    using type = decltype( select_tuple<LAST>()( std::declval<TUPLE>() ) ) ; };
};

int main() {
    using tuple_type = std::tuple<int, std::string, double, char, std::string, int, double> ;
    tuple_type t (8, "house", 3.14, 'b', "apple", 6, 1.5);

  	auto result = select_tuple<1,4,6,2>()(t) ;
  	using expected_type = std::tuple<std::string,std::string,double,double> ;
  	using computed_type = select_tuple<1,4,6,2>::result_type<tuple_type>::type ;


  	static_assert( std::is_same< decltype(result), expected_type >::value, "not ok" );
  	static_assert( std::is_same< decltype(result), computed_type >::value, "not ok" );

  	std::cout << "ok\n" ;
}
