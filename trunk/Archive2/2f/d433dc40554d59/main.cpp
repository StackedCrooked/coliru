#include <iostream>
#include <string>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/list_of.hpp>

int main()
{
    using namespace std;    
    map<string, string> myMap;
    myMap["key1"] = "value1";
    myMap["key1"] = "value2";
    for (auto&& elem : myMap)
        std::cout << "{" << elem.first << ", " << elem.second << "}, ";
    std::cout << "\n";

    using namespace boost::bimaps;
    bimap<set_of<string>, list_of<string>> myMap2;
    myMap2.left["key1"] = "value1";
    myMap2.left["key1"] = "value2";
    for (auto&& elem : myMap2.left)
        std::cout << "{" << elem.first << ", " << elem.second << "}, ";
    std::cout << "\n";
    
    auto res1 = myMap2.left.find("key1");
    std::cout << "{" << res1->first << ", " << res1->second << "} \n";    
}
