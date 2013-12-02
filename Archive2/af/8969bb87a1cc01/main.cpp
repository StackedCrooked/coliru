#include <iostream>
#include <functional>
#include <memory>
#include <stdexcept>

class scanner_impl
{
        explicit scanner_impl( int i = 0 ) : val(i) {}

        int value() const { return val ; }
        int& value() { return val ; }

        void value( int v ) { val = v ; }

        int foobar() const { return val * 5 ; }

        int val ;

        friend class Scanner ;
        friend class std::shared_ptr<scanner_impl> ;
};

struct NullPointerException : virtual public std::runtime_error
{
    using base = std::runtime_error ;
    using base::base ;
    NullPointerException( const char* cstr ) : base(cstr) {}
};

struct OutOfMemoryError : virtual public std::runtime_error
{
    using base = std::runtime_error ;
    using base::base ;
    OutOfMemoryError( const char* cstr ) : base(cstr) {}
};

struct {} null ;

struct Scanner
{
    Scanner() = default ;
    explicit Scanner( int i ) : impl( new (std::nothrow) scanner_impl(i) )
    { if( !impl ) throw OutOfMemoryError("out of memory") ; }
    Scanner( Scanner* ptr ) : impl(ptr->impl) {} // crazy!

    Scanner& operator=( const decltype(null)& ) { impl.reset() ; return *this ; }

    int getValue() /*const*/ { assert_not_null() ; return impl->value() ; }

    void setValue( int v ) { assert_not_null() ; impl->value(v) ; }

    int fooBar() /*const*/ { assert_not_null() ; return impl->foobar() ; }

    private:
        std::shared_ptr<scanner_impl> impl ;
        void assert_not_null() const
        { if( !impl ) throw NullPointerException("NullPointerException") ; }

    friend bool operator== ( const decltype(null)&, const Scanner& s )
    { return !s.impl ;}
};

bool operator!= ( const decltype(null)& n, const Scanner& s ) { return !( n == s ) ;}
bool operator== ( const Scanner& s, const decltype(null)& n ) { return n == s ;}
bool operator!= ( const Scanner& s, const decltype(null)& n ) { return n != s ;}

int main()
{
    Scanner theScanner = new Scanner(25) ;

    std::cout << theScanner.getValue() << ' ' << theScanner.fooBar() << '\n' ;
    theScanner.setValue(100) ;
    std::cout << theScanner.getValue() << '\n' ;

    theScanner = new Scanner( -9 ) ;
    std::cout << theScanner.getValue() << ' ' << theScanner.fooBar() << '\n' ;

    theScanner = null ;

    if( theScanner !=  null ) std::cout << theScanner.getValue() << '\n' ;
    else std::cout << "null reference\n" ;

    try { std::cout << theScanner.getValue() << '\n' ; }
    catch( const std::exception& e ) { std::cerr << e.what() << '\n' ; }
}
