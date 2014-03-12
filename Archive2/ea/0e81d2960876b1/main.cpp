#include <iostream>
#include <tuple>

template<unsigned...Is> struct indexes {typedef indexes<Is...> type;};
template<unsigned min, unsigned max, unsigned...Is> struct make_indexes: make_indexes<min, max-1, max-1, Is...> {};
template<unsigned min, unsigned...Is> struct make_indexes<min, min, Is...>: indexes<Is...> {};

template<unsigned max, unsigned min=0>
using Indexes = typename make_indexes<min, max>::type;

template<typename... Before, typename At, typename... After, unsigned... Bs, unsigned... As>
std::tuple<Before..., At&&, After...> fuze_tuples( indexes<Bs...>, std::tuple<Before...> one, At&& two, indexes<As...>, std::tuple<After...> three)
{
    return { std::get<Bs>(one)..., std::forward<At>(two), std::get<As>(three)... };
}

template<typename... Before, typename At, typename... After>
std::tuple<Before..., At&&, After...> fuze_tuples( std::tuple<Before...> one, At&& two, std::tuple<After...> three)
{
	return fuze_tuples( Indexes< sizeof...(Before) >(), std::move(one), std::forward<At>(two), Indexes< sizeof...(After) >(), std::move(three) );
}

template<unsigned index, typename Functor, typename... Args, unsigned... Before, unsigned... After>
void map_bool_to_compile_time_helper( indexes<Before...>, indexes<After...>, Functor&& f, std::tuple<Args...> args )
{
	if (std::get<index>( args )) {
		std::forward<Functor>(f)( std::get<Before>(args)..., std::true_type(), std::get<After>(args)... );
	} else {
		std::forward<Functor>(f)( std::get<Before>(args)..., std::false_type(), std::get<After>(args)... );
	}
}

template<unsigned index, typename Functor, typename... Args>
void map_bool_to_compile_time( Functor&& f, Args&&... args )
{
	map_bool_to_compile_time_helper<index>( Indexes<index>(), Indexes<sizeof...(Args), index+1>(), std::forward<Functor>(f), std::make_tuple<Args&&...>(std::forward<Args>(args)...) );
}

struct test {
    template<bool b>
    void operator()( int x, std::integral_constant< bool, b > )  { std::cout << x << ": " << b <<"!\n"; } 
};

int main() {
	map_bool_to_compile_time<1>( test(), 1, true );
	map_bool_to_compile_time<1>( test(), 2, false );
}