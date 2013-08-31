template < typename Dest, typename T >
struct FactoryBase
{
    static Dest* create()    // assuming no arguments are necessary, otherwise
    // provide a template parameter pack
    {
        return new T;
    }
};


#include <iostream>

struct base
{};

struct foo
    : public base, public FactoryBase<base, foo>
{
    foo()
    {
        std::cout << "hello world!" << std::endl;
    }
};

struct bar
    : public base, public FactoryBase<base, bar>
{};



#include <map>
#include <string>

int main()
{
    std::map<std::string, base*(*)()> dict;
    dict["foo"] = &foo::create;
    dict["bar"] = &foo::create;
    
    base* p = dict["foo"]();
}
