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
    typedef function_traits<decltype( DoWork )> ftype;
    
    std::cout << typeid( ftype::return_type ).name() <<
        " ( " <<
    std::cout << typeid( ftype::arg0_type ).name() << ", ";
    std::cout << typeid( ftype::arg1_type ).name() << " )" << std::endl;
    
    std::cout << typeid( int ).name() <<
        " ( " <<
    std::cout << typeid( bool ).name() << ", ";
    std::cout << typeid( int ).name() << " )" << std::endl;
}