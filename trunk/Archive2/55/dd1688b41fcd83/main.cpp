#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <type_traits>

struct A
{
    A( const char* cstr ) : ptr( std::make_unique<std::string>(cstr) ) {}

    std::vector<int> vec { 0, 1, 2, 3, 4 } ;
    std::string str = "abcd" ;
    std::unique_ptr<std::string> ptr ;
};

A foo() { return "hello world!" ; }

int main()
{
    std::cout << std::boolalpha << std::is_move_constructible<A>::value << '\n' // true
              << std::is_move_assignable<A>::value << '\n' // true
              << std::is_copy_constructible<A>::value << '\n' // false
              << std::is_copy_assignable<A>::value << '\n' ; // false

    A a = foo() ;
    std::cout << *(a.ptr) << '\n' ; // hello world!

    A a2( std::move(a) ) ;
    std::cout << *(a2.ptr) << '\n' ; // hello world!
}
