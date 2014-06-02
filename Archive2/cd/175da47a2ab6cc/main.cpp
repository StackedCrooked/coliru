#include <iostream>

void foo( const char (&an_array) [100] ) // an_array is (a reference to) an array
{
    std::cout << "sizeof(foo::an_array): " << sizeof(an_array) << '\n' ; // 100
}

void bar( const char an_array[100] ) // an_array is not an array, it is a pointer
{
    std::cout << "sizeof(bar::an_array): " << sizeof(an_array) << '\n' ; // size of pointer
}

int main()
{
    const char this_is_an_array[100] = "C-style string" ;
    std::cout << "array: " << sizeof(this_is_an_array) << '\n' ; // 100

    const char* this_is_a_pointer = this_is_an_array ; // implicit conversion array => pointer
    std::cout << "pointer: " << sizeof(this_is_a_pointer) << '\n' ; // size of pointer

    foo(this_is_an_array) ;

    bar(this_is_an_array) ;
}
