#include <iostream>
#include <ctime>
#include <string>

struct config
{
    enum { NO_ID = 999 };

    struct value_type
    {
        bool a ; operator bool() const { return a ; }
        std::size_t b ; operator std::size_t() const { return b ; }
        std::time_t c ; operator  std::time_t() const { return c ; }
        std::string d ; operator  std::string() const { return d ; }
    };

    value_type getFromDB( int /* id */ ) { /* ... */ throw "something" ; }

    value_type do_getFromDB( int id ) const
    {
        try {  /* ... */ return do_getFromDB(id) ; }
        catch(...) { return { a, b, c, d } ; }
    }

    template < typename T > T get( int id = NO_ID )
    { return id != NO_ID ? getFromDB(id) : value_type{ a, b, c, d } ; }

    private:
        bool a = false ;
        std::size_t b = 492 ;
        std::time_t c = std::time(nullptr) ;
        std::string d = "hello";
};

int main()
{
    config c ;
    std::cout << std::boolalpha << c.get<bool>() << '\n'
              << c.get<std::size_t>() << '\n'
              << c.get<std::time_t>() << '\n'
              << c.get<std::string>() << '\n' ;
}
