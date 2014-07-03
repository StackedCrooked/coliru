#include <iostream>
#include <array>
#include <map>
#include <string>
#include <vector>



struct Point
{ 
    int x = 3; // initializer here
    int y = 4;
};


void test_Point()
{
    Point point;
    std::cout << "Point: " << point.x << ' ' << point.y << std::endl;
}


struct IPv4Address
{ 
    // add begin() and end() methods
    uint8_t* begin() { return bytes; }
    uint8_t* end() { return begin() + sizeof(bytes); }
    
    uint8_t bytes[4] = { 1, 1, 1, 1 }; // initialize all values to one
};


void test_IPv4Address()
{
    IPv4Address ip_address;
    for (uint8_t byte : ip_address)  // detects begin() and end() methods
    {
        std::cout << static_cast<int>(byte) << ' ';
    }
    std::cout << '\n';
}


// alias template is like a typedef
using Name = std::string;


// alias template can be templated:
template<typename T>
using ItemsByName = std::map<Name, T>;


// uniform initialization allows for nice syntax
ItemsByName<int> numbers = {
    { "one", 1 },
    { "two", 2 },
    { "three", 3 }
};


// lambda:
auto one = []{ return 1; }();


// auto:
auto it = numbers.begin();
  // ^ nicer than: std::map<std::string, int>::iterator it = numbers.begin();
  
  
// decltype:
decltype(it) end = numbers.end();
  // ^ deduce the type of it
  

// std::array:
using MACAddress = std::array<uint8_t, 6>;
  // ^ no decay to pointer when passed to a function
  
  
// static_assert + type_traits:
static_assert(std::is_pod<MACAddress>::value, "MACAddress should be POD");

 
struct EthernetHeader
{ 
    MACAddress destination, source;
    uint16_t ethertype;
};
  

// more static assert
static_assert(sizeof(EthernetHeader) == 14, "EthernetHeader should have size of 14 bytes.");
static_assert(std::is_pod<EthernetHeader>::value, "EthernetHeader should be POD");



