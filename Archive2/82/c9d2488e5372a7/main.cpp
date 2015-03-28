#include <iostream>
#include <thread>
#include <atomic>
#include <stdio.h>
 
std::atomic<long long> data;
void do_work()
{
    int g = data.fetch_add(1, std::memory_order_relaxed);
    printf("_%d_", g);
}
 
int main()
{
    std::thread th1(do_work);
    std::thread th2(do_work);
    std::thread th3(do_work);
    std::thread th4(do_work);
    std::thread th5(do_work);
 
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
 
    std::cout << "Result:" << data << '\n';
}