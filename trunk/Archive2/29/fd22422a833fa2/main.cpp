#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

struct person : std::enable_shared_from_this<person> {

    virtual ~person() = default ;
    virtual std::string name() const { return "'" + name_ + "'" ; }

    protected:
        person() = default;
        explicit person ( const std::string& name ) : name_(name) {}

    private: std::string name_ ;

    // non-copyable and non-moveable; always acces via references or (smart) pointers
    person( const person& ) = delete ;
    person& operator= ( const person& ) = delete ;
};

struct person_proxy : person {

    static std::shared_ptr<person_proxy> make( const std::shared_ptr<person>& p ) {
        return std::shared_ptr<person_proxy>( new person_proxy(p) );
    }

    std::shared_ptr<person_proxy> rebind( const std::shared_ptr<person>& p ) {

        show( std::cout << "before rebind: " << this << " => " );  // test

        if( is_cyclic(p) ) throw std::logic_error( "cyclic; can't be proxy for itself" ) ;

        actual = p;
        show( std::cout << "after rebind: " << this << " => " ) ;  // test

        return std::dynamic_pointer_cast<person_proxy>( shared_from_this() ) ;
    }

    virtual std::string name() const override { return actual->name(); }

    private:
        std::shared_ptr<person> actual;
        explicit person_proxy( const std::shared_ptr<person>& p ) : actual( p ) {}

        void show( std::ostream& stm ) {
            #ifndef NDEBUG
                stm << actual.get() ;
                auto p = std::dynamic_pointer_cast<person_proxy>(actual) ;
                if(p) p->show( stm << " => " ) ;
                else stm << '\n' ;
            #endif // NDEBUG
        }

        bool is_cyclic( const std::shared_ptr<person>& p ) const {
            auto pp = std::dynamic_pointer_cast<person_proxy>(p) ;
            if( pp && ( pp.get() == this ) ) return true ;
            else return pp ? is_cyclic( pp->actual ) : false ;
        }
};

struct girl : person {

    static std::shared_ptr<person_proxy> make( const std::string& name ) {
        return person_proxy::make( std::shared_ptr<girl>( new girl(name) ) ) ;
    }

    ~girl() {
        std::cout << "girl::destructor: " << girl::name() << ' ' << this << '\n' ;
    }

    private:
        girl( const std::string& name ) : person( name ) {
            std::cout << "girl::constructor: " << girl::name() << ' ' << this << '\n' ;
        }
};

struct catman : person {

    static std::shared_ptr<person_proxy> make( const std::string& name ) {
        return person_proxy::make( std::shared_ptr<catman>( new catman(name) ) ) ;
    }

    ~catman() {
        std::cout << "catman::destructor: " << catman::name() << ' ' << this << '\n' ;
    }

    private:
        catman( const std::string& name ) : person( name ) {
            std::cout << "catman::constructor: " << catman::name() << ' ' << this << '\n' ;
        }
};

int main() {

    auto a = girl::make( "alice" );
    std::cout << "+++ " << a->name() << " +++\n\n" ;

    auto b = catman::make( "the cheshire catman" );
    a->rebind(b) ;
    std::cout << "+++ " << a->name() << " +++\n\n" ;

    auto c = girl::make( "the queen of hearts" );
    auto d = a->rebind(c) ;
    std::cout << "+++ " << a->name() << " +++\n\n" ;

    try { d->rebind(a) ; } catch( const std::exception& e ) { std::cerr << "***** error: " << e.what() << '\n' ; }
    auto a1 = a ;
    try { c->rebind(a1) ; } catch( const std::exception& e ) { std::cerr << "***** error: " << e.what() << '\n' ; }

    std::cout << "+++ " << a->name() << " +++\n\n" ;
}
