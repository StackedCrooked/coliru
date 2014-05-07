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
    
    protected: template < typename T > class memento_copy_constructor_impl : public memento
    {
        std::unique_ptr<T> copy ;
        memento_copy_constructor_impl( const T& t ) : copy( new T(t) ) {}
        friend T ;
    };
};

struct A : base
{
    virtual void foo( int a, double b ) override { i += a ; d += b ; }
    virtual std::string bar() const override
    { return "A{ " + std::to_string(i) + ", " + std::to_string(d) + " }" ; }

    using memento_type = memento_copy_constructor_impl<A> ;
    
    virtual std::unique_ptr<memento> encapsulated_state() const override
    { return std::unique_ptr<memento>( new memento_type(*this) ) ; }

    virtual void restore_state( const std::unique_ptr<memento>& m ) override
    {
        const memento_type* am = dynamic_cast< const memento_type* >( m.get() ) ;
        if( am == nullptr ) throw std::invalid_argument( "incorrect memento" ) ;
        *this = *am->copy ;
    }

    private:
        int i = 0 ;
        double d = 0 ;
};

int main()
{
    std::unique_ptr<base> p( new A ) ;
    p->foo( 23, 67.89 ) ;
    std::cout << p->bar() << '\n' ; // A{ 23, 67.890000 }

    const auto old_state = p->encapsulated_state() ;

    p->foo( 123, 267.89 ) ;
    std::cout << p->bar() << '\n' ; // A{ 146, 335.780000 }

    p->restore_state(old_state) ;
    std::cout << p->bar() << '\n' ; // A{ 23, 67.890000 }
}