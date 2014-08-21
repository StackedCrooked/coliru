#include <iostream>

//Real stuff
class SomeWrapper
{
    public:
        static int Method(int param)
        {
            return param;
        }
};

//Feeds dummy stuff
class DummyWrapper
{
    public:
        static int Method(int param)
        {
            return 1;
        }
};

//By default it uses the real stuff wrapper
template <class Wrapper = SomeWrapper>
class BasicMyClass
{
    public:
        int DoSomething(int param)
        {
            return Wrapper::Method(param);
        }
};

//typedef for convenience
typedef BasicMyClass<> MyClass;

int main()
{
    MyClass a;
    std::cout << a.DoSomething(-1) << std::endl;
    BasicMyClass<DummyWrapper> b;
    std::cout << b.DoSomething(0) << std::endl;
    return 0;
}