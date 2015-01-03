#include <iostream>
#include <type_traits>

int main()
{
    using function_type = int() ; // nullary function returning int
    typedef int function_type() ; // same as above

    using ptr_function_type = function_type* ; // pointer to function_type
    typedef function_type* ptr_function_type ; // same as above

    using array_type = ptr_function_type[5] ; // array of 5 ptr_function_type
    typedef ptr_function_type array_type[5] ; // same as above

    using ptr_array_type = array_type* ; // pointer to array_type
    typedef array_type* ptr_array_type ; // same as above

    static_assert( std::is_same< int( * (*)[5] )(), ptr_array_type >::value, "must be the same type" ) ;

    int ( * ( * ptr ) [ 5 ] ) ( ) = nullptr ;
    ptr_array_type ptr2 = ptr ;
    static_assert( std::is_same< decltype(ptr), decltype(ptr2) >::value, "must be of the same type" ) ;
}
