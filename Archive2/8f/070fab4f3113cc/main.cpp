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

template<typename T>
struct varint<T,typename std::enable_if<!std::is_integral<T>::value, T>::type> {
    operator T() {return value;}
    T value;
};


int main()
{
    //varint<std::string> test = {"hi there"};
    varint<uint32_t> test = {1};
}
