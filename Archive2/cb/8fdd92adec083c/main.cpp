#include <boost/serialization/singleton.hpp>
#include <iostream>

struct MyConfig : boost::noncopyable
{
    int i;
    MyConfig()       { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    void foo() const { std::cout << __PRETTY_FUNCTION__ << "\n"; }
   ~MyConfig()       { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

int main()
{
    boost::serialization::singleton<MyConfig>::get_const_instance().foo();
}
