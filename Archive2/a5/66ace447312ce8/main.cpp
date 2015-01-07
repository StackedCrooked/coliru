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
    virtual int getId() const {return id;}
public:
    int id = 0;
    std::string name = "";
};

class D : public B
{
    public:
    int getId() const override {return 99;}
};

//this class is called a functor (function object)
//functors are used to enhance standard algorithm behaviours
class getLengthyName
{
    public:
        getLengthyName(unsigned int length) : mLength(length) {};
        
        bool operator()(const std::pair<const int, B>& item)
        {
            return item.second.name.length() > mLength;
        }
    private:
        unsigned int mLength;
};

int main()
{
    
    std::map<int, B> myMap;
    myMap[0] = B{};
    myMap[4] = B{9, "Johny Walker"};
    myMap[2] = B{5, "Jane Doe"};

    std::swap(myMap[0], myMap[2]);
    
//    auto variable;  //compile error - no way to find out a type;

    //playing with lambda functions;
    auto print   = [](const std::pair<const int, B>& item) { std::cout << item.first << ": id[" << item.second.id << "], name[" << item.second.name << "]"<<std::endl; };
    auto lengthy = [](const std::pair<const int, B>& item) { return item.second.name.length() > 8; };
    auto emptyName = [](const std::pair<const int, B>& item) { return item.second.name.empty(); };
    
    //functor style - requires a class somewhere far, far away
    auto itFunct = std::find_if(begin(myMap), end(myMap), getLengthyName(8));
    
    //lambda style - tightly together - preferred.
    auto itLambda = std::find_if(begin(myMap), end(myMap), 
                           [](const std::pair<const int, B>& item) { return item.second.name.length() > 8; });
                           
    //even you can assign a lamda function to an auto variable and use that - just for fun
    auto itLambda2 = std::find_if(begin(myMap), end(myMap), lengthy);
    
    if (itLambda != end(myMap))
    {
        print(*itLambda);
    }
    
    auto count = std::count_if(begin(myMap), end(myMap), lengthy);
    std::cout << "Counted " << count << " lengthy items." << std::endl;
    
    bool hasEmptyName = std::any_of(begin(myMap), end(myMap), emptyName);
    std::cout << "The map " << (hasEmptyName? "has" : "has not") << " empty named item." << std::endl;
    
    //this is the preferred version to walk a collection
    std::cout << std::endl << "Full list:" << std::endl;
    std::for_each(begin(myMap), end(myMap), print);
    
    //other versions:
    //1, walking by hand
    std::cout << std::endl << "Full list (iterating):" << std::endl;
    for( auto iter = begin(myMap); iter != end(myMap) ; ++iter)
    {
        print(*iter);
    }
    //or using range loop
    std::cout << std::endl << "Full list (ranged-loop):" << std::endl;
    for ( auto element : myMap)
    {
        print(element);
    }
    
}
