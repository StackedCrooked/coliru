#include <string>
#include <iostream>
#include <map>

using namespace std;


template <typename A>
void dumpMapReverse(const A &map)
{
    for (auto eachEntry = map.crbegin(); map.crend() != eachEntry; ++eachEntry)
    {
        std::cout << (*eachEntry).first << " - " << (*eachEntry).second << std::endl;
    }
}


int main(void)
{
    map<int, string> mapIS;
    
    cout << "Init 3, 4, 5." << mapIS[3] << mapIS[4] << mapIS[5] << endl;
    
    cout << "\n\tResults:" << endl;
    dumpMapReverse(mapIS);
    
    mapIS[4] = "middle";
    cout << "\n\n\tForced 4 set\n\n\tResults:" << endl;
    dumpMapReverse(mapIS);

    return 0;
    
    
    std::map<std::string,int> my_map;
    
    my_map["y"] = 23;
    my_map["z"] = 24;
    my_map["w"] = 12;
    my_map["x"] = 11;
    
    /*
    auto itit(my_map.cbegin());
    advance(itit, 1);
    auto itit2(itit);
    advance(itit2, 2);
    my_map.erase(itit, itit2);
    */
    
    for (const auto eraseAt(my_map.find("y")); my_map.cend() != eraseAt; )
    {
        my_map.erase(eraseAt);
        break;
    }
    
    dumpMapReverse(my_map);
}