#include <iostream>
#include <string>
#include <thread>
#include <functional>

class MyClass
{
public:
    template<class T>
    void doSomething(T& arg)
    {
        std::cout << arg << " : " << __PRETTY_FUNCTION__ << '\n';
        ++arg;
    }
    
    void runSomething()
    {
        int value = 10;
        std::thread t = std::thread(
                           std::bind(&MyClass::doSomething<int>, this, std::placeholders::_1),
                           std::ref(value));
        t.join();
        std::cout << value << " : " << __PRETTY_FUNCTION__ << '\n';
    }
};

int main()
{
    MyClass mc;
    mc.runSomething();
    return 0;
}