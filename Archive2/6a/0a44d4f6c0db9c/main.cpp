#include <iostream>
#include <array>
#include <string>

template <typename T>
struct A
{
    static T test( const std::string &a  ) { std::cout << "default\n"  ;return T() ; } 
};

template <>
struct A<int>
{
    static inline int test( const std::string &a  )
    {
        std::cout << "int specialization\n" ;
        return 100 ;
        } 
};


template <typename T, int N>
struct A<std::array<T,N>>
{
    static inline std::array<T,N> test( const std::string &a )
    {
        std::array<T,N> arr = {{0}} ;
        std::cout << "std::array<T,N> specialization\n" ;
        return arr ;
    } 
};



struct B
{
    template <typename T>
    inline T get( const std::string &key) const
    {
        return A<T>::test( key ) ;
    }
};


int main()
{
    int x = 10 ;
    std::array<int, 10> arr = {{0}} ;
    B b1; 
      std::cout << A<int>::test("blag") << std::endl ;
      std::cout << (A<std::array<int,10>>::test("blah"))[0] << std::endl ;
      std::cout << (b1.get<std::array<int,10>>( "arggh" ))[0] << std::endl ;
}