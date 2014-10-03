#include <iostream>
#include <thread>
#include <mutex>
#include <thread>
#include <chrono>
 
std::once_flag flag;
 
inline void may_throw_function(bool do_throw)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500 + (rand()%1000)));
  // only one instance of this function can be run simultaneously
  if (do_throw) {
    std::cout << "throw\n"; // this message may be printed from 0 to 3 times
    // if function exits via exception, another function selected
    throw std::exception();
  }
 
  std::cout << "once\n"; // printed exactly once, it's guaranteed that
      // there are no messages after it
}
 
inline void do_once(bool do_throw)
{
  try {
    std::call_once(flag, may_throw_function, do_throw);
  }
  catch (...) {
  }
}
 
int main()
{
    std::thread t1(do_once, true);
    std::thread t2(do_once, true);
    std::thread t3(do_once, false);
    std::thread t4(do_once, true);
 
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}