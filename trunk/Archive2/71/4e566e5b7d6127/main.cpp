#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

template<typename T,typename E=void> struct varint;

template<typename T>
struct varint<T,typename std::enable_if<std::is_integral<T>::value, T>::type> {
    operator T() {return value;}
    T value;
};

template<typename Q>
using varint_t = varint<Q,Q>;


int main()
{
    //varint<std::string> test = {"hi there"};
    varint_t<uint32_t> test = {1};
}
