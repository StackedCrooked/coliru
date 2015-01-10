#include <iostream>
#include <string>
#include <vector>
#include <memory> //new smart-pointers

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Thing
{
    public:
        Thing() = delete;
        Thing(int id) : mId(id){std::cout << "Thing with id " << mId << " created!" << std::endl;};
        ~Thing() {std::cout << "Thing with id " << mId << " deleted!" << std::endl;}
        int getId() {return mId;}
    int mId;
};

std::shared_ptr<Thing> createThing(int id)
{
    return std::shared_ptr<Thing> ( new Thing(id) );
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    
    std::shared_ptr<Thing> p1(new Thing(-9));
    std::shared_ptr<Thing> p9(std::make_shared<Thing>(-66));
    std::shared_ptr<Thing> p2 = p1;
    std::shared_ptr<Thing> p3 = nullptr;
    p3 = p2;
    
    std::cout << "Create new thing." << std::endl;
    p1 = createThing(5);
    std::cout << "delete p2" << std::endl;
    std::cout << p2->getId() << std::endl;
    p2 = nullptr;
    std::cout << "p3 = newthing" << std::endl;
    p3 = p1;
//    Thing a{0};
    //create a local scope
    {
//        Thing x{1};
        std::cout << "End of local scope." << std::endl;
    }
    std::cout << "End of program." << std::endl;
}
