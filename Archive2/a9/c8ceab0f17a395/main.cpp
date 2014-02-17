#include <iostream>
#include <string>
#include <type_traits>

template<class T, bool = false>
struct can_concat : std::false_type {};


template<class T>
struct can_concat<T,std::is_same<decltype( std::string() + std::declval<T>()), std::string>::value>
    : std::true_type {};



int main()
{
    using std::cout;
    using std::endl;
    bool x= can_concat<int()>::value;
    //cout <<  << endl;
}