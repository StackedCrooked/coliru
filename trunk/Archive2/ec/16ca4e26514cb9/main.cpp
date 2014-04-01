#include <typeinfo>
#include <cstdlib>
#include <memory>
#include <string>
#include <cxxabi.h> // GNU
#include <list>
#include <forward_list>
#include <map>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <iostream>
#include <type_traits>

template< typename T > std::string type_name() // GNU
{
    int status ;
    std::unique_ptr< char[], decltype(&std::free) > buffer(
        __cxxabiv1::__cxa_demangle( typeid(T).name(), nullptr, 0, &status ), &std::free ) ;
    return status==0 ? buffer.get() : "__cxa_demangle error" ;
}

#define show_type(a) ( std::cout << "type of " << #a << " is: " << type_name<a>() << '\n' )

int main()
{
    show_type( std::list<int>::allocator_type ) ;
    show_type( std::forward_list<double>::allocator_type ) ;
    
    using map_allocator_type = std::map<std::string,long>::allocator_type ;
    show_type( map_allocator_type ) ;
    
    using namespace boost::interprocess ;
    using my_allocator_type = allocator< int, managed_shared_memory::segment_manager > ;
    using my_list_type = std::list< int, my_allocator_type > ;
    show_type( my_list_type::allocator_type ) ;
    std::cout << "my_list_type::allocator_type is same as my_allocator_type? " << std::boolalpha 
              << std::is_same< my_list_type::allocator_type, my_allocator_type >::value << '\n' ; 
}
