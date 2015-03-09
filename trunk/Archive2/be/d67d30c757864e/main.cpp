#include <iostream>
#include <type_traits>
#include <typeinfo>

template<class T, class U>
constexpr bool is_same_v = std::is_same<T, U>::value;

int main() 
{
    
}