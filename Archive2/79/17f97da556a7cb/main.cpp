#include <iostream>
#include <chrono>
#include <thread>
 
void f()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
 
int main()
{
    auto t1 = std::chrono::high_resolution_clock::now();
    f();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "f() took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds\n";
}