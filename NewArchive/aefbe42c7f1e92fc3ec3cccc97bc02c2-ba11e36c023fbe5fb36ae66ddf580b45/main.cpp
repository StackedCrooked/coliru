#include <functional>
#include <thread>
#include <boost/optional.hpp>


template<typename T>
struct Shared
{
    template<typename ...Args>
    Shared(Args && ...args) :
        obj_(),
        thread_(&Shared<T>::start<Args...>, this, std::forward<Args>(args)...)
    {
    }
    
    template<typename ...Args>
    void start(Args&& ...args)
    {
        //obj_ = T(std::forward<Args>(args)...);
    }
    
    boost::optional<T> obj_;
    std::thread thread_;
};


struct Item
{
    Item(int)
    {
    }
    
    ~Item()
    {
        std::cout << "~Item" << std::endl;
    }
};


int main()
{
    Shared<Item> item(3);
    (void)item;
}