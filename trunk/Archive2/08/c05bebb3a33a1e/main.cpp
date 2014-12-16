#include <iostream>
#include <thread>

int main()
{
    std::thread th([] () { std::cout << "Hello from thread\n"; } );    
    std::cout << "Hello, World!\n";
    th.join();
    return 0;
}