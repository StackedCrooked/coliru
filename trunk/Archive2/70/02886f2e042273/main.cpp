#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

struct variant
{
    using string = std::string ;

    bool is_string() const noexcept { return type == STRING ; }
    bool is_int() const noexcept { return type == INT ; }

    std::string to_string() const
    {
        if( !is_string() ) throw std::logic_error( "not string" ) ;
        return str ;
    }

    int to_int() const
    {
        if( !is_int() ) throw std::logic_error( "not int" ) ;
        return i ;
    }

    variant( const std::string& s ) : type(STRING), str(s) {}
    variant( std::string&& s ) : type(STRING), str( std::move(s) ) {}
    variant( int v = 0 ) noexcept : type(INT), i(v) {}
    variant( const char* cstr ) : type(STRING), str(cstr) {}

    ~variant()  noexcept { if( type == STRING ) str.~string() ; }

    variant( const variant& that ) : type(that.type)
    {
        if( is_string() ) new ( std::addressof(str) ) std::string(that.str) ;
        else i = that.i ;
    }

    variant( variant&& that ) noexcept : type(that.type)
    {
        if( is_string() ) new ( std::addressof(str) ) std::string( std::move(that.str) ) ;
        else i = that.i ;
    }

    variant& operator= ( const variant& that )
    {
        if( this != std::addressof(that) )
        {
            if( is_string() )
            {
                if( that.is_string() ) str = that.str ;
                else { str.~string() ; type = INT ; i = that.i ; }
            }
            else
            {
                if( that.is_int() ) i = that.i ;
                else
                {
                    new ( std::addressof(str) ) std::string(that.str) ;
                    type = STRING ;
                }
            }
        }
        return *this ;
    }

    variant& operator= ( variant&& that ) noexcept
    {
        if( is_string() )
        {
            if( that.is_string() ) str = std::move(that.str) ;
            else { str.~string() ; type = INT ; i = that.i ; }
        }
        else
        {
            if( that.is_int() ) i = that.i ;
            else
            {
                new (&str) std::string( std::move(that.str) ) ;
                type = STRING ;
            }
        }

        return *this ;
    }

    //////////////// TODO /////////////////////////////

    variant& operator= ( const std::string& ) ;
    variant& operator= ( std::string&& ) noexcept ;
    variant& operator= ( int )  noexcept ;
    variant& operator= ( const char* ) ;

    ///////////////////////////////////////////////////

    struct hash
    {
        std::size_t operator() ( const variant& var ) const noexcept
        {
            static const std::hash<std::string> str_hash ;
            static const std::hash<int> int_hash ;
            return var.is_string() ? str_hash(var.str) : int_hash(var.i) ;
        }
    };

    struct equal_to
    {
        bool operator() ( const variant& a, const variant& b ) const noexcept
        {
            if( a.is_string() ) return b.is_string() && a.str == b.str ;
            else return b.is_int() && a.i == b.i ;
        }
    };

    private:

        enum type_t { STRING, INT };
        type_t type ;

        union
        {
            std::string str ;
            int i ;
        };

    friend inline std::ostream& operator<< ( std::ostream& stm, const variant& var )
    { return var.is_string() ? ( stm << '"' << var.str << '"' ) : ( stm << var.i ) ; }
};

int main()
{
    std::unordered_map< variant, std::vector<variant>,
                        variant::hash, variant::equal_to > hash_map ;

    std::pair< variant, variant > key_value_pairs[] =
    {
        { "abcd", "zero" }, { 123, 1 }, { "abcd", 2 }, { 123, 3 }, { "abcd", 4 },
        { 4567, 5 }, { "xyz", 6 }, { 4567, "seven" }, { "xyz", "eight" },
        { "abcd", "nine" }, { "xyz", 10 }, { 4567, 11 }, { 123, "twelve" },
        { "abcd", "thirteen" }, { "xyz", "fourteen" }, { 123, 15 },
        { 123, "sixteen" }, { "abcd", 17 }, { 123, 18 }, { 4567, 19 }, { 123, 20 }
    };

    for( const auto& p : key_value_pairs ) hash_map[p.first].push_back(p.second) ;

    for( const auto& key_value_pair : hash_map )
    {
        std::cout << "key: " << key_value_pair.first << "\n\tvalues: " ;
        for( const variant& v : key_value_pair.second ) std::cout << v << "  " ;
        std::cout << "\n\n" ;
    }
}
