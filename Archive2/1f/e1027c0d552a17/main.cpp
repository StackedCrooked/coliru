#include <iostream>
#include <typeinfo>
 
struct Foo 
{
    virtual ~Foo() {} 
};
struct Bar : public Foo
{ 
    virtual ~Bar() {} 
};
 
int main()
{
    Bar b;
    try {
        Foo& f = dynamic_cast<Foo&>(b);
    } catch(const std::bad_cast& e)
    {
        std::cout <<"In Catch"<<std::endl;
        std::cout << e.what() << '\n';
    }
    std::cout<<"No cast issue"<<std::endl;
}