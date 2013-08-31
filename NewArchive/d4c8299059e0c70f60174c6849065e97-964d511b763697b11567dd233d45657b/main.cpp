#include <array>
#include <functional>
#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>

template<typename T>
using ZipIt = boost::zip_iterator< boost::tuple<T*, T*> >;
 
template<typename T>
using ZipRef = decltype(*ZipIt<T>());

template<typename T>
void operator+=(ZipRef<T> z, T const& v)
{
    z.template get<0>() += v;
    z.template get<1>() += v;    
}
 
int main()
{
    std::array<int, 6> a = { 1, 3, 5, 7,  9, 11 };
    std::array<int, 6> b = { 2, 4, 6, 8, 10, 12 };
    
    std::for_each(
        boost::make_zip_iterator(boost::make_tuple(std::begin(a), std::begin(b))), 
        boost::make_zip_iterator(boost::make_tuple(std::end(a), std::end(b))), 
        [](ZipRef<int> z){ z += 1; }
    );
    
    std::copy(std::begin(a), std::end(a), std::ostream_iterator<int>(std::cout, ",")); std::cout << "\n";
    std::copy(std::begin(b), std::end(b), std::ostream_iterator<int>(std::cout, ",")); std::cout << "\n";
    
    a[2] = 4;
    b[4] = 5;
}