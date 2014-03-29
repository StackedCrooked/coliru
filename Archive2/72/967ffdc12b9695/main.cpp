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
#include <boost/regex.hpp>
#include <boost/cregex.hpp>
#include <vector>

int main()
{
    using namespace boost;

    regex re(".*");

    const std::vector<char> chunkData;

    cregex_iterator reIteratorEnd;
    cregex_iterator reIterator(
            reinterpret_cast<const char*>(chunkData.data()),
            reinterpret_cast<const char*>(chunkData.data()) + chunkData.size(),
            re);
}
