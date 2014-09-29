#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
 
void foo()
{
    // simulate expensive operation
    this_thread::sleep_for(std::chrono::seconds(1));
}
 
void bar()
{
    // simulate expensive operation
    this_thread::sleep_for(std::chrono::seconds(1));
}
 
int main()
{
    cout << "starting first helper...\n";
    thread helper1(foo);
 
    cout << "starting second helper...\n";
    std::thread helper2(bar);
 
    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();
 
    std::cout << "done!\n";
}