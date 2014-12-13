#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>


class B
{
public:
    B() =  default;
    ~B() = default;
    B(int id, std::string name): id(id), name(name) {}
    virtual int getId() const  {return id;}
public:
    int id = 0;
    std::string name = "";
};

class D : public B
{
    public:
    int getId() const override {return 99;}
};

int main()
{
    
    std::map<int, B> myMap;
    myMap[0] = B();
    myMap[5] = B(9, "Johny Walker");
    myMap[3] = B(5, "Jane Doe");

    std::swap(myMap[5], myMap[3]);
    auto print   = [](const std::pair<const int, B>& item) { std::cout << item.first << ": id[" << item.second.id << "], name[" << item.second.name << "]"<<std::endl; };
    auto lengthy = [](const std::pair<const int, B>& item) { return item.second.name.length() > 8; };
    auto emptyName = [](const std::pair<const int, B>& item) { return item.second.name.length() == 0; };
    
    auto it = std::find_if(begin(myMap), end(myMap), lengthy);
    if (it != myMap.end())
    {
        print(*it);
    }
    auto count = std::count_if(begin(myMap), end(myMap), lengthy);
    std::cout << "Counted " << count << " lengthy items." << std::endl;
    
    bool hasEmptyName = std::any_of(begin(myMap), end(myMap), emptyName);
    std::cout << "The map " << (hasEmptyName? "has" : "has not") << " empty named item." << std::endl;
    
    std::cout << std::endl << "Full list:" << std::endl;
    std::for_each(begin(myMap), end(myMap), print);
    

}
