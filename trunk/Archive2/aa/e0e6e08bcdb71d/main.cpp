#include <iostream>
#include <type_traits>

namespace my_library
{
    namespace noncopyable____detail____
    {
        struct noncopyable
        {
            noncopyable() noexcept = default ;
            ~noncopyable() noexcept = default ;

            noncopyable( const noncopyable& ) = delete ;
            noncopyable& operator= ( const noncopyable& ) = delete ;

            // note: move constructor implicitly declared as deleted
            // note: move assignment implicitly declared as deleted
        };
    }
    using noncopyable = noncopyable____detail____::noncopyable ;
}

struct A : private my_library::noncopyable {};

int main()
{
    std::cout << std::boolalpha
              << std::is_copy_constructible<A>::value << '\n' // false
              << std::is_move_constructible<A>::value << '\n' // false
              << std::is_copy_assignable<A>::value << '\n' // false
              << std::is_move_assignable<A>::value << '\n' ; // false

    A x ;
    // A x1(x) ; // *** error: A( const A& ) is deleted
    // A x2 ( std::move(x) ) ; // *** error: A( A&& ) is deleted

    A y ;
    // y = x ; // *** error: A& operator= ( const A& ) is deleted
    // y = std::move(x) ; // *** error: A& operator= ( A&& ) is deleted
}
