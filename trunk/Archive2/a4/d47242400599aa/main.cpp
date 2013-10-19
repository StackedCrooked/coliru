#include <iostream>
#include <thread>

void worker()
{
    std::cout << "another thread";
}

int main()
{
    std::thread t(worker);
    std::cout << "main thread" << std::endl;
    t.join();
    return 0;
}