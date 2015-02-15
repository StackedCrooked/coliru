#include <memory>
#include <iostream>

struct A
{
    ~A() { std::cout << "A::destructor\n" ; /* .. */ }; // destructor is public

    // static factory functions to create dynamically allocated objects
    template < typename... ARGS > static std::unique_ptr<A> make_unique( ARGS&&... args )
    { return std::unique_ptr<A>( make_new( std::forward<ARGS>(args)...  ) ) ; }

    template < typename... ARGS > static std::shared_ptr<A> make_shared( ARGS&&... args )
    { return std::shared_ptr<A>( make_new( std::forward<ARGS>(args)... ) ) ; }

    // ...

    private:
        // constructors are private
        A( /* ... */ ) { /* ... */ }
        A( int /* ... */ ) { /* ... */ } // another constructor
        A( const A& ) { /* ... */ }
        A( A&& ) noexcept = default ;

        // ...

        template < typename... ARGS > static A* make_new( ARGS&&... args )
        { return new A( std::forward<ARGS>(args)... ) ; }

        // ....
};

int main()
{
    auto p = A::make_unique( 200 /* ... */ ) ;
    auto p1 = A::make_shared(*p) ;
    // etc.
}
