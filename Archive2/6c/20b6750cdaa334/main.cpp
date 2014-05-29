#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <string>
std::atomic<int> data;
void do_work()
{
    data.fetch_add( 1 );
}


int main(int argc,char** argv)
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
    std::cout<<data.load()<<std::endl;
    return 0;
}