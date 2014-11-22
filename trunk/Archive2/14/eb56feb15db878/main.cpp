#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


std::mutex mutex;

void foo() {
   std::chrono::milliseconds const timeout(400);
    
   for (int i = 1; i <= 10; ++i) {      
      std::this_thread::sleep_for(timeout);
       
      std::lock_guard<std::mutex> const guard(mutex);
   	  std::cout << i << timeout.count() << " ms" << std::endl;
   }   
}

int main() {   
   std::chrono::milliseconds const timeout(200);
   
   std::thread thread(foo);
     
   for (int i = 1; i <= 10; ++i) {
      std::this_thread::sleep_for(timeout);
       
      std::lock_guard<std::mutex> const guard(mutex);
      std::cout << i << timeout.count() << " ms" << std::endl;
   }
   
   thread.join();
}
