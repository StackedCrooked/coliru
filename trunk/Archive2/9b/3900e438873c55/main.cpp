#include <iostream>
#include <thread>

void a() { a(); }


int main()
{
    std::thread([]{
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "Infinite recursion\n";
        std::exit(1);
    }).detach();
    
    a();
    std::cout << "Ok" << std::endl;
}
