#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

struct sheep
{
    int id ;
    std::string destination ;
    // ....
};

struct destination
{
    std::string port_name ;
    // ....
};

std::vector<sheep> make_shipping_list( std::vector<sheep> sheep_list, std::vector<destination> port_list )
{
    const auto not_to_a_port_in_list = [&port_list] ( sheep s )
    {
        for( destination d : port_list ) if( s.destination == d.port_name ) return false ;
        return true ;
    };

    sheep_list.erase( std::remove_if( std::begin(sheep_list), std::end(sheep_list), not_to_a_port_in_list ),
                      std::end(sheep_list) ) ;

    std::sort( std::begin(sheep_list), std::end(sheep_list),
               [] ( sheep a, sheep b ) { return a.destination < b.destination ; } ) ;

    return sheep_list ;
}

int main()
{
    const std::vector<sheep> sheep_list =
    {
        { 1, "Gibralter" }, { 2, "Kobe" }, { 3, "Aberdeen" }, { 4, "Oslo" }, { 5, "Alexandra" },
        { 6, "Alexandra" }, { 7, "Gibralter" }, { 8, "Tripoli" }, { 9, "Antwerp" }, { 10, "Aberdeen" },
        { 11, "Malmo" }, { 12, "Hull" }, { 13, "Oslo" }, { 14, "Kobe" }, { 15, "Alexandra" }, { 16, "Tripoli" }
    };

    const std::vector<destination> port_list = { { "Tripoli" }, { "Aberdeen" }, { "Alexandra" }, { "Antwerp" } } ;

    for( sheep s : make_shipping_list( sheep_list, port_list ) )
        std::cout << "sheep# " << std::setw(2) << s.id << " to " << s.destination << '\n' ;
}
