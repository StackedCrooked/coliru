#include <string>
#include <iostream>
#include <map>
 
int main()
{
    std::map<std::string,int> my_map;
    my_map["x"] =  11;
    my_map["y"] = 23;
 
    auto it = my_map.find("x");
    if (it != my_map.end()) std::cout << "A: " << it->second << "\n";
 
    it = my_map.find("z");
    if (it != my_map.end()) std::cout << "B: " << it->second << "\n";
 
    // Accessing a non-existing element creates it
    if (my_map["z"] == 42) std::cout << "Oha!\n";
 
    it = my_map.find("z");
    if (it != my_map.end()) std::cout << "C: " << it->second << "\n";
}