#include <string>
#include <iostream>
#include <map>
 
int main()
{
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
    
    for (auto eachEntry = my_map.crbegin(); my_map.crend() != eachEntry; ++eachEntry)
    {
        std::cout << (*eachEntry).first << " - " << (*eachEntry).second << std::endl;
    }
}