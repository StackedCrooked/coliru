#include <iostream>
#include <typeinfo>

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

template<typename R, typename T0, typename T1, typename T2>
struct function_traits<R ( T0, T1, T2 )> {
public:
	typedef R return_type;
	typedef T0 arg0_type;
	typedef T1 arg1_type;
	typedef T2 arg2_type;
	typedef R (*func_type)( T0, T1, T2 );

};

template<typename R, typename T0, typename T1, typename T2, typename T3>
struct function_traits<R ( T0, T1, T2, T3 )> {
public:
	typedef R return_type;
	typedef T0 arg0_type;
	typedef T1 arg1_type;
	typedef T2 arg2_type;
	typedef T3 arg3_type;
	typedef R (*func_type)( T0, T1, T2, T3 );

};

template<typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
struct function_traits<R ( T0, T1, T2, T3, T4 )> {
public:
	typedef R return_type;
	typedef T0 arg0_type;
	typedef T1 arg1_type;
	typedef T2 arg2_type;
	typedef T3 arg3_type;
	typedef T4 arg4_type;
	typedef R (*func_type)( T0, T1, T2, T3, T4 );

};

template<typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct function_traits<R ( T0, T1, T2, T3, T4, T5 )> {
public:
	typedef R return_type;
	typedef T0 arg0_type;
	typedef T1 arg1_type;
	typedef T2 arg2_type;
	typedef T3 arg3_type;
	typedef T4 arg4_type;
	typedef T5 arg5_type;
	typedef R (*func_type)( T0, T1, T2, T3, T4, T5 );

};


int main ( int argc, char** argv ) {

	typedef function_traits<decltype( main )> ftype;

	std::cout << typeid( ftype::return_type ).name() <<
		" ( " << typeid( ftype::arg0_type ).name() << ", ";
	std::cout << typeid( ftype::arg1_type ).name() << " )" << std::endl;

	std::cout << typeid( int ).name() <<
		" ( " << typeid( bool ).name() << ", ";
	std::cout << typeid( char** ).name() << " )" << std::endl;

}