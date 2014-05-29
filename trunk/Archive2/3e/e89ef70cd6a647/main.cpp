#include <iostream>
#include <string>
#include <vector>
#include <boost/ptr_container/ptr_map.hpp>

class MyClass
{
public:
    int stuff;
};

std::string const& GetName()
{
    static std::string const name("test");
    return name;
}

int main()
{
    typedef boost::ptr_map<std::string, MyClass> PtrMap;
    
    std::auto_ptr<MyClass> myptr(new MyClass());

    PtrMap mymap;
    mymap.insert(GetName(), myptr);
    
    std::cout << mymap.size() << std::endl;
}