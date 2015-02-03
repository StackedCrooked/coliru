#include <iostream>
#include <utility>

struct A
{
    std::string name ;

    A( const std::string& str ) : name(str) { std::cout << "A::constructor (copy string)\n" ; }
    A( const std::string&& str ) : name( std::move(str) ) { std::cout << "A::constructor (move string)\n" ; }

    ~A() { std::cout << "A::destructor\n" ; }

    A( const A& that ) : name( that.name ) { std::cout << "A::copy_constructor\n" ; }
    A( A&& that )  noexcept : name( std::move( that.name ) ){ std::cout << "A::move_constructor\n" ; }

    A& operator= ( const A& that ) { name = that.name ; std::cout << "A::copy_assignment\n" ; return *this ; }
    A& operator= ( A&& that )  noexcept { name = std::move( that.name ) ; std::cout << "A::move_assignment\n" ; return *this; }

    std::string& who() & { return name ; } // return lvalue of type std::string
    const std::string& who() const& { return name ; } // return lvalue of type const std::string
    std::string who() && { return std::move(name) ; } // return prvalue of type std::string
 };

struct container
 {
    A a ;

    container( const A& aa ) : a(aa) { std::cout << "container::constructor (copy A)\n" ; }
    container( const A&& aa ) : a( std::move(aa) ) { std::cout << "container::constructor (move A)\n" ; }

    ~container() { std::cout << "container::destructor\n" ; }

    container( const container& that ) : a( that.a ) { std::cout << "container::copy_constructor\n" ; }
    container( container&& that )  noexcept : a( std::move( that.a ) ){ std::cout << "container::move_constructor\n" ; }

    container& operator= ( const container& that ) { a = that.a ; std::cout << "container::copy_assignment\n" ; return *this ; }
    container& operator= ( container&& that )  noexcept { a = std::move( that.a ) ; std::cout << "container::move_assignment\n" ; return *this; }
};

A make_a( std::string str ) { return A( std::move(str) ) ; }

int main()
{
    {
        A a { "Elmer Fudd" } ;
        std::cout << a.who() << '\n' // calls A::who() &
                  << const_cast< const A& >(a).who() << '\n' ; // calls A::who() const&

        std::cout << std::move(a).who() << '\n' ; // calls A::who() &&

        std::cout << "size: " << a.who().size() << '\n' ; // 0, the string was moved
        // for exposition only. do not do this (only the destructor should access an object after it has been moved)
    }
    std::cout << "-------------------\n" ;

    A a { "Daffy Duck" } ;

    { container one(a) ; } std::cout << "-------------------\n" ;  // copy A

    { container two( make_a("Bugs Bunny") ) ; } std::cout << "-------------------\n" ; // move A

    // try assignment etc.
}
