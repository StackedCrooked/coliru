#include <iostream>
#include <memory>
#include <utility>
#include <string>

struct A_impl // only dynamic storage duration is supported
{
    using pointer = std::unique_ptr<A_impl> ;

    // for exposition only
    // assume that we have a good reason to enforce creation via factory function
    // for instance: A_impl is a flyweight
    //               A_impl needs to be placed into non-pageable memory
    //               etc.
    template< typename... ARGS > static pointer make( ARGS&&... args )
    { return pointer( new A_impl( std::forward<ARGS>(args)... ) ) ; }

    int value() const { return value_ ; }
    std::string name() const { return name_ ; }
    // ...

    A_impl& operator= ( const A_impl& ) = default ;
    A_impl& operator= ( A_impl&& ) = default ;

    private:
        int value_ = 8 ;
        std::string name_ ;

        A_impl() = default ;
        explicit A_impl( int v ) : value_(v) {}
        A_impl( int v, std::string& s ) : value_(v), name_(s) {}
        A_impl( int v, std::string&& s ) noexcept : value_(v), name_( std::move(s) ) {}
        A_impl( const A_impl& ) = default ;
        A_impl( A_impl&& ) noexcept = default ;
};

struct A // syntactic sugar
{
    template< typename... ARGS >
    explicit A( ARGS&&... args ) : impl( A_impl::make( std::forward<ARGS>(args)... ) ) {}

    // copy is a deep copy
    A( A& that ) : impl( A_impl::make( that.value(), that.name() ) ) {}
    A( const A& that ) : impl( A_impl::make( that.value(), that.name() ) ) {}

    // move is normal move
    A( A&& that ) noexcept = default ;

    // likewise for operator =

    int value() const { return impl->value() ; }
    std::string name() const { return impl->name() ; }
    // ...

    private: A_impl::pointer impl ;
};

A foo() { return A( 23, "abcd" ) ; }

int main()
{
    A a( 17, "hello" ) ;
    std::cout << a.value() << ' ' << a.name() << '\n' ;

    A copy_of_a(a) ;
    std::cout << copy_of_a.value() << ' ' << copy_of_a.name() << '\n' ;

    A moved_to( foo() ) ; // move construct from prvalue
    std::cout << moved_to.value() << ' ' << moved_to.name() << '\n' ;
}
