#include <iostream>
#include <functional>
#include <type_traits>

using std::cout;
using std::endl;

template<typename TFuncSignature>
struct function_traits;

template<typename R>
struct function_traits<R ()> {
public:
    typedef R return_type;
    typedef R (*func_type)( );

};

template<typename R, typename T0>
struct function_traits<R ( T0 )> {
public:
    typedef R return_type;
    typedef T0 arg0_type;
    typedef R (*func_type)( T0 );

};

template<typename R, typename T0, typename T1>
struct function_traits<R ( T0, T1 )> {
public:
    typedef R return_type;
    typedef T0 arg0_type;
    typedef T1 arg1_type;
    typedef R (*func_type)( T0, T1 );

};

int DoWork (bool, int) {
    return 1;
}

int main() {    
    
    std::cout << typeid( function_traits<decltype( DoWork )>::return_type ).name() <<
        " ( " <<
    std::cout << typeid( function_traits<decltype( DoWork )>::arg0_type ).name() << ", ";
    std::cout << typeid( function_traits<decltype( DoWork )>::arg1_type ).name() << " )" << std::endl;
}