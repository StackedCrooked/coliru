#include <iostream>
#include <thread>

struct MyFunctionObject {
    void operator() () 
    {
        std::cerr << "Hello function object" << std::endl;
    }
};

int main()
{
    std::thread t {MyFunctionObject {}};
    t.join();
}