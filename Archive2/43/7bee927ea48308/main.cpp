#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

struct items
{
    items(std::string name) : name(name) {}
    std::string name;
};

using std::string;
using std::vector;

namespace cxx11
{
    items string_to_item( string item_name, const vector<items>& item_container )
    {
        auto result = std::find_if(item_container.begin(), item_container.end(), 
                                   [&](items const& it) {
                                       return it.name == item_name;
                                   });
        if(result == item_container.end()) {
            if(item_container.size() == 0) {
                std::cout << "no elements in vector  ( get_item )";
            }
            return items("null");
        }
        
        return *result;
    }
}

namespace cxx03
{
    items string_to_item( string item_name, const vector<items>& item_container )
    {
        struct comparer
        {
            comparer(std::string const& item_name) : item_name(item_name) {}
            bool operator()(items const& it) const { return it.name == item_name; }
            std::string const& item_name;
        } comp(item_name);
        
        auto result = std::find_if(item_container.begin(), item_container.end(), comp);
        if(result == item_container.end()) {
            if(item_container.size() == 0) {
                std::cout << "no elements in vector  ( get_item )";
            }
            return items("null");
        }
        
        return *result;
    }
}

int main()
{
    std::vector<items> item_container;
    
    cxx11::string_to_item("foo", item_container);
    cxx03::string_to_item("foo", item_container);
}
