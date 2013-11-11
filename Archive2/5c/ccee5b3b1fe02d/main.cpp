#include <iostream>
#include <thread>
#include <mutex>
 
std::once_flag flag;
 
void do_once()
{
    auto f = [](){ std::cout << "Called once" << std::endl; };
    //std::call_once(flag, f);
    f();
}
 
int main()
{
    std::thread t1(do_once);
    std::thread t2(do_once);
    std::thread t3(do_once);
    std::thread t4(do_once);
 
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}