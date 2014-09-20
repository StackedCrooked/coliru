#include <iostream>
#include <string>
#include <functional>

struct uart
{
    void do_put_data( unsigned char )
    { std::cout << "uart::do_put_data for uart '" << name << "' at " << this << '\n' ; }

    uart( std::string name ) : name(name) {}
    std::string name ;

    using data_put_t = std::function< void( unsigned char ) > ;
    const data_put_t data_put() { return std::bind( &uart::do_put_data, this, std::placeholders::_1 ) ; }
};

int main ()
{
    uart one("one"), two("two"), three("three"), four("four") ;

    uart::data_put_t data_put[] { one.data_put(), two.data_put(), three.data_put(), four.data_put() } ;

    for( const auto& put : data_put ) put(10) ;
}
