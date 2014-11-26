//Title of this code

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/array.hpp>

template<typename T, std::size_t N>
std::string operator+ ( const boost::array<T,N>& arr, const std::string & x )
{
    std::string s;
 for( const auto& i:arr)
    s += std::to_string(i) ;
 return s+x ;
}

template<typename T, std::size_t N>
std::string operator+ (  const std::string & x, const boost::array<T,N>& arr  )
{
    std::string s;
 for( const auto& i:arr)
    s += std::to_string(i) ;
 return x+s ;
}

int main()
{
    boost::array<int, 3> a = {1, 2, 3};
    boost::array<int, 3> b = {4, 5, 6};
    
   std::string s = a + "abc" + b ;
   std::cout << s ;
}