#include <iostream>
#include <thread>


int main()
{
    int xi = 0;
    //Launch a thread
    std::thread t1([&]()
    {
        std::cout << "Hello, World" << std::endl;
        xi += 10;
    });

    //Join the thread with the main thread
    t1.join();

    std::cout << "xi = " << xi << std::endl;
    return 0;
}
