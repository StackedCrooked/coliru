#include <cstddef>
#include <iostream>
#include <type_traits>

template<typename T, std::size_t N>
struct is_special
: 
    std::false_type 
{};

template<std::size_t N>
struct is_special<float, N>
: 
    std::integral_constant<bool, !(N % 4)> 
{};

template<std::size_t N>
struct is_special<double, N>
: 
    std::integral_constant<bool, !(N % 2)> 
{};

template<typename, std::size_t, typename = void>
class vec_base;

template<typename T, std::size_t N>
class vec_base<T, N, typename std::enable_if<!is_special<T, N>::value>::type> 
{
public:
    static void print() { std::cout << "vec_base<T, N>\n"; };    
};

template<std::size_t N>  
class vec_base<float, N, typename std::enable_if<!(N % 4)>::type>
{
public:
    static void print() { std::cout << "vec_base<float, 4 * K>\n"; };    
};

template<std::size_t N> 
class vec_base<double, N, typename std::enable_if<is_special<double, N>::value>::type>
{
public:
    static void print() { std::cout << "vec_base<double, 2 * K>\n"; };    
};

int main()
{
    vec_base<int, 6>::print();
    vec_base<float, 1>::print();
    vec_base<float, 4>::print();
    vec_base<double, 1>::print();
    vec_base<double, 2>::print();
}
