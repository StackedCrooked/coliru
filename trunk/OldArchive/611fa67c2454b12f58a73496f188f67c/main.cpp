#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
 
 
struct Blocker
{
  Blocker(unsigned n) : n(n) {}
 
  void notify()
  {
    std::unique_lock<std::mutex> lock (m);
    if (n)
    {
        n--;
    }
    c.notify_all (); 
  }
 
  void wait()
  {
    std::unique_lock<std::mutex> lock (m);
    while (n)
    {
      c.wait (lock);
    }
  }
 
  unsigned n;
  std::mutex m;
  std::condition_variable c;
};
 
template<typename Callback>
void async_operation(const Callback & cb) { cb(); }
 
 
int main()
{
    Blocker b(2);
    async_operation([&](){ b.notify(); });
    async_operation([&](){ b.notify(); });
    b.wait();
    
    std::cout << "End of program." << std::endl;
}