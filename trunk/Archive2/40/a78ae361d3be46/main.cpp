#include <iostream>
#include <utility>
#include <boost/thread.hpp>
#include <chrono>
#include <functional>
#include <atomic>
 
void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 1 executing\n";
        ++n;
        //std::boost::this_thread::sleep_for(std::chrono::milliseconds(10));
        boost::this_thread::sleep(boost::posix_time::milliseconds(10));
    }
}
 
void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 executing\n";
        ++n;
        //std::boost::this_thread::sleep_for(std::chrono::milliseconds(10));
        boost::this_thread::sleep(boost::posix_time::milliseconds(50));
    }
}
 
int main()
{
    int n = 0;
    boost::thread t1; // t1 is not a thread
    boost::thread t2(f1, n + 1); // pass by value
    boost::thread t3(f2, std::ref(n)); // pass by reference
   boost::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    t2.join();
    t4.join();
    std::cout << "Final value of n is " << n << '\n';
}