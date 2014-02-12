#include <iostream>
#include <thread>
#include <memory>


struct MyClass {
    std::unique_ptr<std::thread> T;
    
    void startThreadDetach()
    {
        T.reset( new std::thread( &MyClass::myThreadMethod, this ));
        T->detach();
    }
    
    void startThreadJoin()
    {
        T.reset( new std::thread( &MyClass::myThreadMethod, this ));
        T->join();
    }
    
    void myThreadMethod()
    {
        // ...
    }
};

int main()
{
    MyClass x;
    x.startThreadDetach();
    x.startThreadJoin();
}
