#include <iostream>
#include <thread>
#include <mutex>
 
std::once_flag flag;
 
void do_once(int i)
{
    std::call_once(flag, [i](){ std::cout << "Called once " << i << std::endl; });
}
 
int main()
{
    std::thread t1(do_once, 0);
    std::thread t2(do_once, 1);
    std::thread t3(do_once, 2);
    std::thread t4(do_once, 3);
 
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}