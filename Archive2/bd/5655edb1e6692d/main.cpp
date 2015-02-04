#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>

template<typename T,typename E=void> struct varint;

template<typename T>
struct varint<T,typename boost::enable_if_c<boost::is_integral<T>::value>::type> {
    operator T() {return value;}
    T value;
};


int main()
{
    //varint<std::string> test = {"hi there"};
    varint<uint32_t> test;
}
