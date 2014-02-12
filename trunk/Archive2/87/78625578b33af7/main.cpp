#include <iostream>
#include <thread>
#include <memory>


struct MyClass {
    std::unique_ptr<std::thread> T;
    
    void startThread()
    {
        T.reset( new std::thread( &MyClass::myThreadMethod, this ));
    }
    
    void myThreadMethod()
    {
        // ...
    }
};

int main()
{
    MyClass x;
    x.startThread();
}
