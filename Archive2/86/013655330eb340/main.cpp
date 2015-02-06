
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class Bar;

class Foo{
    public:
    Foo() : i(99) {}
    friend class Bar;
 private:
 int i;
    
};



class Bar {
    static void Test(Foo foo){
        std::cout <<    foo.i;
    }
    
};



int main(void)
{
   
   Foo foo;
   Bar::Test(foo);

}

