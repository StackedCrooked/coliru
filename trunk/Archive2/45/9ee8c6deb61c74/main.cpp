#include <type_traits>
#include <tuple>

template < typename... TUPLES > struct tuple_cat_result
{
    using reference_to_function = decltype( std::tuple_cat< TUPLES... > )& ; 
    using type = typename std::result_of< reference_to_function(TUPLES...) >::type ;
};

int main()
{
    static_assert( std::is_same< tuple_cat_result< std::tuple<short,int,long>, std::tuple<float,double> >::type,
                   std::tuple<short,int,long,float,double> > ::value, "*** not ok ***" ) ;
}
