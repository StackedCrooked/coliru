#include <iostream>
#include <cstdint>
#include <type_traits>
 
template<size_t N, typename T = void>
struct index_type_;
 
template<size_t N>
struct index_type_<N, typename std::enable_if<N <= 0xFF>::type>
{
    typedef uint8_t type;
};
 
template<size_t N>
struct index_type_<N, typename std::enable_if<N <= 0xFFFF>::type>
{
    typedef uint16_t type;
};
 
template<size_t N>
struct index_type_<N, typename std::enable_if<N <= 0xFFFFFFFF>::type>
{
    typedef uint32_t type;
};
 
template<size_t N>
struct index_type_<N, typename std::enable_if<N <= 0xFFFFFFFFFFFFFFFF>::type>
{
    typedef uint64_t type;
};
 
int main()
{
    index_type_<32>::type index1;
    index_type_<232122>::type index2;
    index_type_<992532523>::type index3;
    index_type_<4213662352328854>::type index4;
     
    std::cout << "index1:" << sizeof(index1) << std::endl;
    std::cout << "index2:" << sizeof(index2) << std::endl;
    std::cout << "index3:" << sizeof(index3) << std::endl;
    std::cout << "index4:" << sizeof(index4) << std::endl;
}