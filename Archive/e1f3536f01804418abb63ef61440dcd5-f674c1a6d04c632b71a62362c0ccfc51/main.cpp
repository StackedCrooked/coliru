#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <map>


typedef std::map<std::string, std::string> Properties;


class Item : Properties
{
public:
    Item(std::string inName) : mName(std::move(inName))
    {
    }
    
    const std::string& name() const { return mName; }
    
    using Properties::begin;
    using Properties::end;
    using Properties::operator[];
    
private:
    friend bool operator<(const Item& lhs, const Item& rhs)
    { return lhs.name() < rhs.name(); }
    
    std::string mName;
};


typedef std::deque<Item> Items;


int main()
{
    Item item1("item1");
    item1["id"] = std::to_string(1);
    item1["album"] = "gold";
    item1["artist"] = "abba";
    item1["timestamp"] = std::to_string(time(0));
    
    
    for (auto& kp : item1)
    {
        std::cout << kp.first << "=" << kp.second << std::endl;
    }
}
