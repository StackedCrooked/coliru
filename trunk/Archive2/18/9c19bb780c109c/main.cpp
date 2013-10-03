#include <type_traits>

template<typename... Ts>
struct list {};

using my_int_list = list<std::integral_constant<int,0>,
                         std::integral_constant<int,1>,
                         std::integral_constant<int,2>>;
                         
                         
template<typename LIST>
struct to_array;

template<typename... Ts>
struct to_array<list<Ts...>>
{
    static constexpr unsigned int result[] = { Ts::value... };
}; 

template<typename LIST>
struct to_2d_array;

template<typename... Ts>
struct to_2d_array<list<Ts...>>
{
    using value_type = unsigned int; //To simplify things, suppose we know the type
                                     //of the elements. Also suppose the array is 
                                     //squared.

    static constexpr value_type result[sizeof...(Ts)][sizeof...(Ts)] = { to_array<Ts>::result... };
};

int main()
{
    to_2d_array<list<my_int_list,my_int_list,my_int_list>> a;
}
