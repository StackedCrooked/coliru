#include <iostream>

namespace foo
{
    struct StaticStuff
    {
        int x; int y;  
    };
    
    StaticStuff const & getStaticStuff()
    {
        static StaticStuff s{ .x = 1234, .y = 5678 };
        return s;
    }
}

namespace bar
{
    class Bar
    {
    public:
        ////////////// vvvv  here
        Bar() :
           Bar(foo::getStaticStuff().x, foo::getStaticStuff().y)
        { }
        
        Bar(int x, int y)
        { }
    };
    
}

int main(void)
{

}