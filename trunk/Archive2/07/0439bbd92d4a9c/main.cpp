#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

int main()
{
    const std::vector<std::string> counties =
    {
        "grandIsle", "franklin", "orleans", "essex", "chittenden", "lamoille",
        "caledonia", "addison", "washington", "orange", "rutland", "windsor",
        "bennington", "windham"
    };

    const std::vector< std::vector<std::string> > neighbours =
    {
         { "franklin", "chittenden" },
         { "grandIsle", "chittenden", "lamoille", "orleans" },
         { "franklin", "lamoille", "caledonia", "essex" },
         { "orleans", "caledonia" },
         { "grandIsle", "franklin", "lamoille", "washington", "addison" },
         { "franklin", "orleans", "caledonia", "washington", "chittenden" },
         { "orleans", "essex", "orange", "washington", "lamoille" },
         { "chittenden", "washington", "orange", "windsor", "rutland" },
         { "lamoille", "caledonia", "orange", "addison", "chittenden" },
         { "washington", "caledonia", "windsor", "addison" },
         { "addison", "windsor", "bennington" },
         { "addison", "orange", "rutland", "windham" },
         { "rutland", "windsor", "windham" },
         { "windsor", "bennington" }
    };

    const std::set< std::string > colours =
    {
        "1RED", "2GREEN", "3BLUE", "4YELLOW", "5MAGENTA",
        "6CYAN", "7WHITE", "8BLACK", "9zzzz" // "9zzzz" == unassigned
    };

    // colours are 1, 2, 3, ... n
    std::vector<std::string> county_colours( counties.size(), "9zzzz" ) ; // initially unassigned

    // greedy
    for( std::size_t i = 0 ; i < counties.size() ; ++i )
    {
        const std::vector<std::string>& adjacent_counties = neighbours[i] ;

        std::set<std::string> unavailable_colours ;
        for( const std::string& county : adjacent_counties )
        {
            auto pos = std::find( counties.begin(), counties.end(), county ) - counties.begin() ;
            unavailable_colours.insert( county_colours[pos] ) ;
        }

        std::vector< std::string > possible_colours ;
        std::set_difference( colours.begin(), colours.end(),
                               unavailable_colours.begin(), unavailable_colours.end(),
                               std::back_inserter(possible_colours) ) ;

        county_colours[i] = possible_colours.front() ; // pick the first possible colour
        std::cout << counties[i] << " - " << county_colours[i].substr(1) << '\n' ;
    }
}
