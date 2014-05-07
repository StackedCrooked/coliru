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

    private: class A_memento : public base::memento
    {
        std::unique_ptr<A> copy_of_a ;
        A_memento( const A& a ) : copy_of_a( new A(a) ) {}
        friend struct A ;
    }; public:

    virtual std::unique_ptr<memento> encapsulated_state() const override
    { return std::unique_ptr<memento>( new A_memento(*this) ) ; }

    virtual void restore_state( const std::unique_ptr<memento>& m ) override
    {
        const A_memento* am = dynamic_cast< const A_memento* >( m.get() ) ;
        if( am == nullptr ) throw std::invalid_argument( "incorrect memento") ;
        *this = *am->copy_of_a ;
    }

    private:
        int i = 0 ;
        double d = 0 ;
};

int main()
{
    std::unique_ptr<A> p( new A ) ;
    p->foo( 23, 67.89 ) ;
    std::cout << p->bar() << '\n' ; // A{ 23, 67.890000 }

    const auto old_state = p->encapsulated_state() ;

    p->foo( 123, 267.89 ) ;
    std::cout << p->bar() << '\n' ; // A{ 146, 335.780000 }

    p->restore_state(old_state) ;
    std::cout << p->bar() << '\n' ; // A{ 23, 67.890000 }
}
