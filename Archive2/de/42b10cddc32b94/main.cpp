#include <thread>
#include <iostream>
#include <chrono>
void f()
{
    std::cout << "Output from thread...";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "...thread calls flush()\n";
    std::cout.flush();
}
 
int main()
{
    std::thread t1(f);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::clog << "Output from main\n";
    t1.join();
}