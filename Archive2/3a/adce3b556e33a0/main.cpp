#include <iostream>
#include <string>
struct A{
    void method()
    {
        std::cout<<"Hello"<<std::endl;
    }
};


int main()
{
    //object o;
    A *o=0;
    o->method();
    return 0;
}
