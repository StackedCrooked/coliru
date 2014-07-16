#include <iostream>
#include <thread>
#include <mutex>

void foo(int id, std::ostream& os)
{
  thread_local int i = 0;
  for(; i < 1000; ++i)
  {
   
    os <<id << ":" << i << std::endl;
  }
}

int main() {
  std::thread t1(foo, 256, std::ref(std::cout));
 
  foo(255, std::cout);  
  t1.join();
  return 0;
}
