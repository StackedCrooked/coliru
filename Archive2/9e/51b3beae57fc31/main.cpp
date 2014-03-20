#include <string>
#include <typeinfo>
#include <cxxabi.h>
#include <cstdlib>
#include <memory>

template< typename T > std::string type_name()
{
    int status ;
    std::unique_ptr< char[], decltype(&std::free) > buffer(
        __cxxabiv1::__cxa_demangle( typeid(T).name(), nullptr, 0, &status ), &std::free ) ;
    return status==0 ? buffer.get() : "__cxa_demangle error" ;
}

template< typename T > std::string type_name( const T& ) { return type_name<T>() ; }
#define print_type_name(var) ( std::cout << #var << " is of type " << type_name(var) << "\n\n" )

#include <boost/multiprecision/cpp_int.hpp>

int main()
{
    const boost::multiprecision::cpp_int max = 6;
    const boost::multiprecision::cpp_int factor = 4;

    // type: boost::multiprecision::detail::expression<>
    const auto raw_result_a = factor * factor ;
    const auto raw_result_b = max/factor ;

    // type: boost::multiprecision::number<>
    const boost::multiprecision::cpp_int integer_result_a(raw_result_a) ;
    const boost::multiprecision::cpp_int integer_result_b(raw_result_b) ;

    std::cout << "multiply raw results: " << raw_result_a * raw_result_b << '\n' // 24
              << "multiply int results: " << integer_result_a * integer_result_b << "\n\n" ; // 16

    print_type_name(raw_result_a) ; // boost::multiprecision::detail::expression<...>
    print_type_name(integer_result_a) ; // boost::multiprecision::number<...>
}
