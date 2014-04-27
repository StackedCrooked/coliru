#include <cstddef>
#include <iostream>
#include <type_traits>

template<typename T, std::size_t N, std::size_t B = 128>
struct is_special
: 
    std::integral_constant<bool, std::is_floating_point<T>::value && 8 * sizeof(T) * N == B> 
{};

template<typename, std::size_t, typename = void>
class vec_base
{
public:
    static void print() { std::cout << "vec_base<T, N>\n"; };    
};

template<std::size_t N>  
class vec_base<float, N, typename std::enable_if<is_special<float, N>::value>::type>
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
