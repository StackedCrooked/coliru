#include <tuple>
#include <algorithm>
#include <utility>
#include <iostream>



template<std::size_t... Indices , typename Tuple , typename T>
bool find_in_tuple_impl( std::integer_sequence<std::size_t,Indices...> , const Tuple& t , const T& e )
{
    bool result[] = { (std::get<Indices>( t ) == e)... };

    return std::any_of(std::begin(result) , std::end(result) , [](bool b){ return b; } );
}

template<typename... ARGS , typename T>
bool find_in_tuple( const std::tuple<ARGS...>& t , const T& e )
{
    return find_in_tuple_impl( std::index_sequence_for<ARGS...>{} , t , e );   
}


int main()
{
    auto t = std::make_tuple(1,2.0f,true,'c');
    
    std::cout << std::boolalpha << find_in_tuple(t , 'c') << std::endl;
}