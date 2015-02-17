#include <iostream>
#include <vector>
#include <string>

struct map_segment
{
    map_segment( std::string  ) { /* ... */ } // note: not explicit

    // ...
};

struct map_segment_a
{
    map_segment_a( std::string area_name ) { /* ... */ } // note: not explicit

    // delegating constructor http://www.stroustrup.com/C++11FAQ.html#delegating-ctor
    map_segment_a( const char* area_name ) : map_segment_a( std::string(area_name) ) {} // not explicit

    // ...
};

int main()
{
    const map_segment maps[] { std::string("Forest"), std::string("Home"), std::string("Dungeon") } ;
    const map_segment_a maps_a[] { "Forest", "Home", "Dungeon" } ;
}
