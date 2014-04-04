#include <iostream>
#include <thread>

int a() { return 0 + a(); }


int main()
{
    std::thread([]{
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "Infinite recursion\n";
        std::exit(1);
    }).detach();
    
    std::cout << a() << std::endl;
}
