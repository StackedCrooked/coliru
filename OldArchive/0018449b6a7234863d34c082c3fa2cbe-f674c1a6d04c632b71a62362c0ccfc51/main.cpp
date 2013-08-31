#include <boost/strong_typedef.hpp>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <map>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


typedef std::string PropertyName;
typedef std::string PropertyValue;
typedef std::map<PropertyName, PropertyValue> Properties;


template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::map<T, U>& map)
{
    os << "(properties";
    for (auto& el : map)
    {
        os << " (" << el.first << ' ' << el.second << ")";
    }
    return os << ")";
}


struct Item : private Properties
{
    explicit Item(uint32_t inId) : mId(inId) {}
    
    uint32_t id() const { return mId; }
    
    using Properties::begin;
    using Properties::end;
    using Properties::operator[];
    
private:
    friend bool operator<(const Item& lhs, const Item& rhs)
    { return lhs.id() < rhs.id(); }
    
    friend std::ostream& operator<<(std::ostream& os, const Item& item)
    {
        const Properties& properties = item;
        return os << "(item (id " << item.id() << ") " << properties << ")";
    }
    
    uint32_t mId;
};


typedef std::deque<Item> Items;
typedef std::deque<uint32_t> Ids;
typedef std::map<PropertyName, Ids> Index;




int main()
{
    Item item1{1};
    item1["name"] = "fernando";
    item1["album"] = "gold";
    item1["artist"] = "abba";
    
    Item item2{2};
    item2["name"] = "i am the city";
    item2["album"] = "more gold";
    item2["artist"] = "abba";
    
    std::cout << "Item1: " << item1 << std::endl;
    std::cout << "Item2: " << item2 << std::endl;
}
