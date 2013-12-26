#include <memory>
#include <string>
#include <iostream>

struct base
{
    struct state { virtual ~state() {} } ;
    using memento = std::shared_ptr<state> ;

    virtual ~base() {}
    virtual memento current_state() const = 0 ;
    virtual void restore_state( const memento& m ) = 0 ;

    virtual std::unique_ptr<base> clone() const = 0 ;

    virtual std::ostream& print( std::ostream& ) const = 0 ;
    // ...

    friend inline std::ostream& operator<< ( std::ostream& stm, const base& b )
    { return b.print(stm) ; }

    protected:
        base() = default ;
        base( const base& ) = default ;
        base( base&& ) = default ;
        base& operator= ( const base& ) = delete ;
};

struct derived : base
{
    derived( const std::string& name, int value ) : name_(name), value_(value) {}

    std::string name() const { return name_ ; }
    void name( const std::string& name ) { name_ = name ; }

    int value() const { return value_ ; }
    void value( int value ) { value_ = value ; }

    virtual memento current_state() const override
    { return memento{ new state( name(), value() ) }; }

    virtual void restore_state( const memento& m ) override
    {
        auto s = dynamic_cast< const state* >( m.get() ) ;
        if(!s) throw std::domain_error( "invalid state " ) ;
        name_ = s->name ;
        value_ = s->value ;
    }

    virtual std::unique_ptr<base> clone() const override
    { return std::unique_ptr<base>{ new derived(*this) } ; }

    virtual std::ostream& print( std::ostream& stm ) const override
    { return stm << "derived{ '" << name() << "', " << value() << " }" ; }

    // ...

    private:
        class state : public base::state
        {
            state( const std::string& name, int value ) : name(name), value(value) {}
            std::string name ;
            int value ;
            friend class derived ;
        };

        std::string name_ ;
        int value_ ;

        derived( const derived& ) = default ;
        derived( derived&& ) = default ;
};

void foo( const base* b ) 
{
    std::cout << "original: " << *b << '\n' ;
    auto clone = b->clone() ;
    std::cout << "clone: " << *clone << '\n' ;
}

int main()
{
    derived d { "test", 1234 } ;

    base* b = &d ;
    foo(b) ;

    auto m = b->current_state() ;

    d.name( "*** modified *** " ) ;
    d.value( -9999 ) ;

    std::cout << *b << '\n' ;

    b->restore_state(m) ;
    std::cout << *b << '\n' ;
}
