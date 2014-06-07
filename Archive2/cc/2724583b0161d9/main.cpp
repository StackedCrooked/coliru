#include <map>
#include <string>
#include <iostream>

struct TestStruct
{
   int superInt;
   std::string superString;
};

int main()
{
    std::map< std::string, TestStruct > myMap;
    
    myMap[ "testKey" ] = { 100500, "omg" };
}


