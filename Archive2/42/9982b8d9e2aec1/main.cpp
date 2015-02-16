#include <iostream>
#include <string>
#include <vector>

#include <atomic>

namespace cw{
namespace core{
namespace concurrent{

    template<class T>
    class atomical_property;            

}// namespace concurrent
}// namespace core
}// namespace cw

template<class T>
class cw::core::concurrent::atomical_property{
public:
    atomical_property(){
        property_value.store(0);
    }

    operator T(){
        return property_value.load();
    }

  /*  operator +(const T& other){
        return property_value.load() + other;
    }

    operator -(const T& other){
        return property_value.load() - other;
    }*/

    void operator=(T other){
        property_value.store(other);
    }

private:
    std::atomic<T> property_value;
};//class atomical_property


int main()
{
    cw::core::concurrent::atomical_property<bool> the_bool;
    bool boolean;
    boolean = the_bool;
    
    std::cout << boolean << std::endl;
}
