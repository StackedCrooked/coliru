#include <iostream>
#include <utility>
#include <tuple>

template<typename T, typename U>
struct my_meta_function;

template<typename U, int... Is>
struct my_meta_function<std::integer_sequence<Is...>, U>
{
    typedef decltype(std::make_tuple((Is, std::declval<U>())...)) type;
};

template<int N, typename U>
struct my_meta_function<N, U>
    : my_meta_function<std::make_integer_sequence<N>, U>
{
};
 
int main()
{
    
}