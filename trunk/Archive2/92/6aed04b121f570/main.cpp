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
    
    template<class T>
    void runSomething(T& value)
    {
        std::thread t = std::thread(
                           std::bind(&MyClass::doSomething<T>, this, std::placeholders::_1),
                           std::ref(value));
        t.join();
        std::cout << value << " : " << __PRETTY_FUNCTION__ << '\n';
        ++value;
    }
};

int main()
{
    MyClass mc;
    
    int value = 10;
    mc.runSomething(value);
    std::cout << value << " : " << __PRETTY_FUNCTION__ << '\n';
    
    return 0;
}