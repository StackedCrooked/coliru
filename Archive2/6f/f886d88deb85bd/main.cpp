#include <iostream>
#include <string>
#include <boost/variant.hpp>

boost::variant<int,double> to_number( std::string str )
{
    try
    {
        std::size_t pos = 0 ;
        int value = std::stoi( str, std::addressof(pos), 0 ) ;
        if( pos == str.size() ) return value ;
    }
    catch( const std::exception& ) {}

    return std::stod(str) ;
}

int main()
{
    struct print_it : boost::static_visitor<void>
    {
       void operator() ( int value ) const { std::cout << "int: " << value << '\n' ; }
       void operator() ( double value ) const { std::cout << "double: " << value << '\n' ; }
    };

    for( std::string str : { "1234", "1234.5", "-99", "0777", "0xff", "-0x1ff.7p-2", "inf", "-infinity", "NaN", "hello" } )
    {
        std::cout << str << " => " ;
        try
        {
            const auto var = to_number(str) ;
            boost::apply_visitor( print_it(), var ) ;
        }
        catch( const std::exception& ) { std::cerr << "**** error: no conversion could be performed\n" ; }
    }
}
