#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

struct base
{
    virtual ~base() = default ;
    virtual void foo( int, double ) = 0 ;
    virtual std::string bar() const = 0 ;


    struct memento { virtual ~memento() = default ; };

    virtual std::unique_ptr<memento> encapsulated_state() const = 0 ;
    virtual void restore_state( const std::unique_ptr<memento>& m ) = 0 ;
};

struct A : base
{
    virtual void foo( int a, double b ) override { i += a ; d += b ; }
    virtual std::string bar() const override
    { return "A{ " + std::to_string(i) + ", " + std::to_string(d) + " }" ; }

    class A_memento : public base::memento
    {
        int i ;
        double d ;
        A_memento( const A& a ) : i(a.i), d(a.d) {}
        friend struct A ;
    };

    virtual std::unique_ptr<memento> encapsulated_state() const override
    { return std::unique_ptr<memento>( new A_memento(*this) ) ; }

    virtual void restore_state( const std::unique_ptr<memento>& m ) override
    {
        const A_memento* am = dynamic_cast< const A_memento* >( m.get() ) ;
        if( am == nullptr ) throw std::invalid_argument( "incorrect memento") ;
        i = am->i ;
        d = am->d ;
    }

    private:
        int i = 0 ;
        double d = 0 ;
};

int main()
{
    std::unique_ptr<A> p( new A ) ;
    p->foo( 23, 67.89 ) ;
    auto old_state = p->encapsulated_state() ;

    p->foo( 123, 267.89 ) ;
    std::cout << p->bar() << '\n' ;

    p->restore_state(old_state) ;
    std::cout << p->bar() << '\n' ;
}
