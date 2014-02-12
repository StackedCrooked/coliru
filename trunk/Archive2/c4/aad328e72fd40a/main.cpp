#include <functional>
#include <iostream>

struct Test
{
    int x = 20;
    int fnc(int  a) { x = a; return x; }
};

int main ()
{
    typedef std::function<void(int)> Func;

    //int i = 10;
    Test t;
    t.x = 5;
    
    //std::function<void()> f = std::bind(&Test::fnc, &t, i);
    
    //f();
    
    //std::cout << t.x;
    
    
    //std::function<void(int)> g = std::bind(&Test::fnc, &t, std::placeholders::_1);
    //g(2000);
    
    std::function<void(Test,int)> g = std::bind(&Test::fnc, std::placeholders::_1, std::placeholders::_2);
    
    g(t, 2000);
    
    std::cout << t.x;
}
