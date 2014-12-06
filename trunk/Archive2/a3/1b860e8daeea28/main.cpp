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
    // sort sheep_list on destination
    std::sort( std::begin(sheep_list), std::end(sheep_list),
               [] ( sheep a, sheep b ) { return a.destination < b.destination ; } ) ;

    // sort port_list on port_name
    std::sort( std::begin(port_list), std::end(port_list),
               [] ( destination a, destination b ) { return a.port_name < b.port_name ; } ) ;

    std::vector<sheep> shipping_list ;

    auto sheep_iter = std::begin(sheep_list) ;
    for( const destination& dest : port_list ) // for each port in port list
    {
        // skip over the sheep bound for destinations before this destination
        while( sheep_iter != std::end(sheep_list) && sheep_iter->destination < dest.port_name ) ++sheep_iter ;

        // add the sheep bound for this particular destinations to the shipping list
        while( sheep_iter != std::end(sheep_list) && sheep_iter->destination == dest.port_name )
        {
            shipping_list.push_back( *sheep_iter ) ;
            ++sheep_iter ;
        }
    }

    return shipping_list ;
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
