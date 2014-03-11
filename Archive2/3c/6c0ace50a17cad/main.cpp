#include <iostream>
#include <tuple>

template<unsigned...Is> struct indexes {typedef indexes<Is...> type;};
template<unsigned min, unsigned max, unsigned...Is> struct make_indexes: make_indexes<min, max-1, max-1, Is...> {};
template<unsigned min, unsigned...Is> struct make_indexes<min, min, Is...>: indexes<Is...> {};

template<unsigned max, unsigned min=0>
using Indexes = typename make_indexes<min, max>::type;

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

template<typename Functor, unsigned... indexes>
struct map_bools_to_compile_time_helper;

template<typename Functor, unsigned index, unsigned... indexes>
struct map_bools_to_compile_time_helper<Functor, index, indexes...> {
    Functor&& f;
    map_bools_to_compile_time_helper(Functor&& in):f(std::forward<Functor>(in)) {}
    template< typename... Args>
    void operator()( Args&&... args) const {
        map_bool_to_compile_time<index>( map_bools_to_compile_time_helper<Functor, indexes...>{std::forward<Functor>(f)}, std::forward<Args>(args)... );
    }
};
template<typename Functor>
struct map_bools_to_compile_time_helper<Functor> {
    Functor&& f;
    map_bools_to_compile_time_helper(Functor&& in):f(std::forward<Functor>(in)) {}
    template<typename... Args>
    void operator()( Args&&... args) const {
        std::forward<Functor>(f)(std::forward<Args>(args)...);
    }
};

template<unsigned... Is, typename Functor, typename... Args>
void map_bools_to_compile_time( indexes<Is...>, Functor&& f, Args&&... args ) {
    map_bools_to_compile_time_helper<Functor, Is...>{ std::forward<Functor>(f) }( std::forward<Args>(args)... );
}


struct test {
    template<bool b>
    void operator()( int x, std::integral_constant< bool, b > )  { std::cout << x << ": " << b <<"!\n"; } 
};

struct test2 {
    template<bool b0, bool b1, bool b2>
    void operator()( int x, std::integral_constant< bool, b0 >, std::integral_constant< bool, b1 >, std::integral_constant< bool, b2 > )
    {
        std::cout << x << ": " << b0 << b1 << b2 << "\n";
    }
};
int main() {
	map_bools_to_compile_time( indexes<1>(), test(), 1, true );
	map_bool_to_compile_time<1>( test(), 2, false );
    map_bools_to_compile_time( indexes<1,2,3>(), test2(), 3, true, false, true );
}