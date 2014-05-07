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

template < typename DERIVED > struct memento_copy_constructor_impl : base
{
    protected: 
        class memento_type : public base::memento
        {
            std::unique_ptr<DERIVED> copy ;
            explicit memento_type( const DERIVED& d ) : copy( new DERIVED(d) ) {}
            friend memento_copy_constructor_impl<DERIVED> ;
        };
    
    public: virtual std::unique_ptr<memento> encapsulated_state() const override
    { return std::unique_ptr<memento>( new memento_type( dynamic_cast<const DERIVED&>(*this) ) ) ; }

    virtual void restore_state( const std::unique_ptr<memento>& m ) override
    {
        const memento_type* am = dynamic_cast< const memento_type* >( m.get() ) ;
        if( am == nullptr ) throw std::invalid_argument( "incorrect memento" ) ;
        dynamic_cast<DERIVED&>(*this) = *am->copy ;
    }
};

struct A : memento_copy_constructor_impl<A>
{
    virtual void foo( int a, double b ) override { i += a ; d += b ; }
    virtual std::string bar() const override
    { return "A{ " + std::to_string(i) + ", " + std::to_string(d) + " }" ; }

    private:
        int i = 0 ;
        double d = 0 ;
};

struct B : memento_copy_constructor_impl<B>
{
    virtual void foo( int a, double b ) override { str = std::to_string(a) + std::to_string(b) ; }
    virtual std::string bar() const override { return "B{ '" + str + "' }" ; }

    private: std::string str ;
};

int main()
{
    for( auto& p : { std::unique_ptr<base>( new A ), std::unique_ptr<base>( new B ) } )
    {
        p->foo( 23, 67.89 ) ;
        std::cout << "first: " << p->bar() << '\n' ; 
    
        const auto old_state = p->encapsulated_state() ;
    
        p->foo( 123, 267.89 ) ;
        std::cout << "second: " << p->bar() << '\n' ; 
    
        p->restore_state(old_state) ;
        std::cout << "restored: " << p->bar() << "\n----------------------------\n" ; 
    }
}