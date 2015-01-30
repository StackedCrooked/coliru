#include <string>
#include <set>
#include <map>
#include <list>

int main()
{
    using namespace std;

    using Mypaths = set < string > ;
    using Mapdata = map < string, list < set < string >::iterator > >;
    
    Mapdata myMap;
    Mypaths paths { "left", "right", "up", "down" };
    
    // Fill a temporary list with iterators...
    
    list< set<string>::iterator > temp;
    
    temp.push_back( paths.find("left") );
    temp.push_back( paths.find("up") );
    
    // ... and then add the list to the map
    
    myMap["left and up"] = temp;
    
    // Or do it directly within the map:
    
    myMap["right and down"].push_back( paths.find("right") );
    myMap["right and down"].push_back( paths.find("down") );

}