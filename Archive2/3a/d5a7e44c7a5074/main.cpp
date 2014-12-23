#include <iostream>
#include <thread>
#include <atomic>
 
std::atomic<long long> data;
long long udata;
void do_work()
{
    for (int i = 0; i < 100000; i++)
    {
        data.fetch_add(1, std::memory_order_relaxed);
        udata++;
    }
}
 
int main()
{
    std::thread th1(do_work);
    std::thread th2(do_work);
    std::thread th3(do_work);
    std::thread th4(do_work);
    std::thread th5(do_work);
    std::thread th6(do_work);
    std::thread th7(do_work);
    std::thread th8(do_work);
    std::thread th9(do_work);
 
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    th9.join();
 
    std::cout << "Result:" << data << '\n';
    std::cout << "Result:" << udata << '\n';
}