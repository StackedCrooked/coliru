#include <thread>
#include <mutex>
#include <iostream>

using namespace std;
int g_i = 0;
std::mutex g_i_mutex;  // protects g_i
 
void safe_increment()
{
    std::lock_guard<std::mutex> lock(g_i_mutex);
    ++g_i;
 
    // g_i_mutex is automatically released when lock
    // goes out of scope
}
 
int main()
{
    std::thread t1(safe_increment);
    std::thread t2(safe_increment);
 
    cout << g_i;
    t1.join();
    t2.join();
}